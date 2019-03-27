/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019 Jan Starke <jan.starke@outofbed.org>

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

#ifndef PROJECT_APICONTEXT_H
#define PROJECT_APICONTEXT_H

typedef int c_regex_ptr;
typedef int c_iterator_ptr;

const c_regex_ptr c_regex_none = 0;
const c_iterator_ptr c_iterator_none = 0;

#ifdef __cplusplus
#include <librexgen/regex/regex.h>
#include <librexgen/iterator/iterator.h>
#include <map>
#include <mutex>
#include <memory>

class ApiContext {
public:
  inline static ApiContext& instance() {
    static ApiContext ctx;
    return ctx;
  }

  inline c_regex_ptr addRegex(std::shared_ptr<rexgen::Regex> regex);
  inline c_iterator_ptr addIterator(std::shared_ptr<rexgen::Iterator> iter);

  inline void deleteRegex(const c_regex_ptr& id);
  inline void deleteIterator(const c_iterator_ptr& id);

  inline std::shared_ptr<rexgen::Regex>& getRegex(const c_regex_ptr& id);
  inline std::shared_ptr<rexgen::Iterator>& getIterator(const c_iterator_ptr& id);

private:
  ApiContext() : _id(0){}

  inline int next_id() { return (++_id); }

  std::map<c_regex_ptr, std::shared_ptr<rexgen::Regex>> regex_map;
  std::map<c_iterator_ptr, std::shared_ptr<rexgen::Iterator>> iterator_map;
  int _id;
};

c_regex_ptr ApiContext::addRegex(std::shared_ptr<rexgen::Regex> regex) {
  auto id = next_id();
  assert(id != c_regex_none);
  regex_map.insert(std::make_pair(id, regex));
  return id;
}
c_iterator_ptr ApiContext::addIterator(std::shared_ptr<rexgen::Iterator> iter) {
  auto id = next_id();
  assert(id != c_iterator_none);
  iterator_map.insert(std::make_pair(id, iter));
  return id;
}

void ApiContext::deleteRegex(const c_regex_ptr& id) {
  regex_map.erase(id);
}
void ApiContext::deleteIterator(const c_iterator_ptr& id) {
  iterator_map.erase(id);
}

std::shared_ptr<rexgen::Regex>& ApiContext::getRegex(const c_regex_ptr& id) {
  return regex_map.at(id);
}
std::shared_ptr<rexgen::Iterator>& ApiContext::getIterator(const c_iterator_ptr& id) {
  return iterator_map.at(id);
}

#endif

#endif /* PROJECT_APICONTEXT_H */
