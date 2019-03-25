/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019  Jan Starke <jan.starke@outofbed.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/


#include <librexgen/parser/rexgenparsingdriver.h>
#include <librexgen/parser/RexgenFlexLexer.h>
#include <algorithm>
#include <utility>
#include <cstring>
#include <sstream>
#include <istream>
#include <ostream>
#include "parser.hpp"

namespace rexgen {
  RexgenParsingDriver::RexgenParsingDriver(const RexgenOptions &__options)
          : result(nullptr),
            groupId(1),
            options(__options),
            streamRegex(nullptr) {
  }

  std::shared_ptr<rexgen::Regex> RexgenParsingDriver::parse(const std::string& regex) {
    result = nullptr;
    scanner = std::make_shared<RexgenFlexLexer>(regex);
    parser = std::make_shared<RexgenParser>(scanner, *this);
    if (0 == parser->parse()) {
      return getResult();
    } else {
      return nullptr;
    }
  }

/**
 * iterates through all group references and calls
 * updateGroupReferences for each
 */
  void RexgenParsingDriver::updateAllGroupReferences() {
    for (auto p : groups) {
      if (auto ptr = p.second.lock())
      updateGroupReferences(p.second);
    }
  }

  void RexgenParsingDriver::updateGroupReferences(const std::weak_ptr<Regex>& wre) {
    if (auto re = wre.lock()) {
      for (auto ref : groupRefs) {
        for (auto gr : (*ref.second)) {
          if (ref.first == re->getGroupId()) {
            gr->setRegex(re);
          }
        }
      }
    }
  }

  bool RexgenParsingDriver::hasInvalidGroupReferences() const {
    bool invalids = false;
    for (auto ref : groupRefs) {
      for (auto gr : *(ref.second)) {
        invalids |= (gr->getRegex().expired() == false);
      }
    }
    return invalids;
  }

  void RexgenParsingDriver::registerGroupReference(std::shared_ptr<GroupReference> gr) {
    /* this is needed to later set the refered Regex */
    decltype(groupRefs)::iterator references = groupRefs.find(gr->getGroupId());
    if (references == groupRefs.end()) {
      groupRefs[gr->getGroupId()] = std::make_shared<std::set<std::shared_ptr<GroupReference> >>();
      references = groupRefs.find(gr->getGroupId());
    }
    (*references).second->insert(gr);
  }

  const std::shared_ptr<std::set<std::shared_ptr<GroupReference>>>& RexgenParsingDriver::getGroupReferences(
          int id) const {
    return groupRefs.at(id);
  }

  void RexgenParsingDriver::registerGroup(std::weak_ptr<Regex>& wre) {
    if (auto re = wre.lock()) {
      groups.insert(std::make_pair(re->getGroupId(),wre));
    }
  }

  const std::weak_ptr<Regex>& RexgenParsingDriver::getGroupRegex(int id) const {
    return groups.at(id);
  }

  const std::map<int, std::weak_ptr<Regex>> &RexgenParsingDriver::getGroups() const {
    return groups;
  }

  std::shared_ptr<Regex> RexgenParsingDriver::getStreamRegex() {
    if (streamRegex == nullptr) {
      streamRegex = std::make_shared<StreamRegex>(options.stream_callback);
      return streamRegex;
    } else {
      std::shared_ptr<GroupReference> gr = std::make_shared<GroupReference>(streamRegex->getId());
      gr->setRegex(streamRegex);
      return gr;
    }
  }
}