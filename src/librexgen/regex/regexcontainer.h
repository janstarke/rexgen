/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
*/

#ifndef __regexcontainer_h__
#define __regexcontainer_h__

#include "regex.h"
#include <deque>
#include <algorithm>
#include "../debug.h"
#include <librexgen/simplestring.h>

using namespace std;

class RegexContainer : public Regex {
public:
  virtual ~RegexContainer() {
    for_each(regexObjects.begin(), regexObjects.end(), [](Regex* re)
      {delete re;});
  }
  
  virtual int getMaxSize() const {
    auto iter = regexObjects.begin();
    int __size = 0;
    while (iter != regexObjects.end()) {
      __size += (*iter)->getMaxSize();
      iter++;
    }
    return __size * getMaxOccurs();
  }
  
  void appendContent(SimpleString& dst, int level) const {
    for_each(regexObjects.cbegin(), regexObjects.cend(),
      [&](const Regex* re) {
        appendSpace(dst, level);
        re->appendRawValue(dst, level);
    });
  }
  
  unsigned int size() { return getChildren()->size(); }

protected:
  deque<Regex*>* getChildren() { return &regexObjects; }
  deque<Regex*> regexObjects;
};

#endif
