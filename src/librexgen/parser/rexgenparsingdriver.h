/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

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


#ifndef SRC_LIBREXGEN_PARSER_REXGENPARSERCONTEXT_H_
#define SRC_LIBREXGEN_PARSER_REXGENPARSERCONTEXT_H_

#include <librexgen/regex/streamregex.h>
#include <librexgen/regex/groupreference.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/regexalternatives.h>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cstdio>
#include <memory>
#include <sstream>
#include <FlexLexer.h>

namespace rexgen {
  class RexgenParsingDriver;
  class RexgenFlexLexer;
  class RexgenParser;
}

namespace rexgen {
  class Regex;

  class RexgenParsingDriver {
  public:
    RexgenParsingDriver(const RexgenOptions &__options);

    int nextGroupId() { return groupId++; }

    bool hasGroupId(int id) const { return (groups.find(id) != groups.end()); }

    std::shared_ptr<rexgen::Regex> parse(const std::string& regex);

    void registerGroupReference(std::shared_ptr<GroupReference> gr);

    const std::shared_ptr<std::set<std::shared_ptr<GroupReference>>>& getGroupReferences(int id) const;

    void registerGroup(std::weak_ptr<Regex>& re);

    const std::weak_ptr<Regex>& getGroupRegex(int id) const;

    const map<int, std::weak_ptr<Regex>> &getGroups() const;

    void updateAllGroupReferences();

    void updateGroupReferences(const std::weak_ptr<Regex>& wre);

    bool hasInvalidGroupReferences() const;

    FILE *getInFile() const { return options.infile; }

    callback_fp_mb getStreamCallback() const { return options.stream_callback; }

    void handleParserError(const char *msg) const {
      if (options.parser_error) {
        options.parser_error(msg);
      }
    }

    void setResult(const std::shared_ptr<Regex> &regex) {
      assert(this->result == nullptr);
      this->result = regex;
      assert(this->result != nullptr);
    }

    std::shared_ptr<Regex> getResult() {
      return result;
    }
/*
    inline bool hasNextChar() const { return (next_char != ascii_input.cend()); }

    inline const char& getNextChar() const { ++next_wc_char; return *next_char++; };

    inline wchar_t getCurrentChar() const { return current_char; }
*/
    /** this is the handling of `\0` - terminals in the regex. the first occurance
     * of `\0` creates a StreamRegex and returns it, all following occurances
     * return a reference to the previously created StreamRegex.
     * We must make this distinction, because StreamReference handles
     * calls to next() by going to the next word, and calling next() for
     * the whole regex would result in multiple calls to next() for each single
     * occurance of `\0`. So, we return a GroupReference, which does not forward
     * the invocation of next() to the StreamRegex
     */
    std::shared_ptr<Regex> getStreamRegex();

  private:

    std::shared_ptr<Regex> result;

    int groupId;
    const RexgenOptions &options;
    std::map<int, std::shared_ptr<std::set<std::shared_ptr<GroupReference>>>> groupRefs;
    std::map<int, std::weak_ptr<Regex>> groups;
    std::shared_ptr<StreamRegex> streamRegex;
    std::shared_ptr<RexgenFlexLexer> scanner;
    std::shared_ptr<RexgenParser> parser;
  };
}
#endif  // SRC_LIBREXGEN_PARSER_REXGENPARSERCONTEXT_H_
