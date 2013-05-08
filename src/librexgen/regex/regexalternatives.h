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


#ifndef REGEXALTERNATIVES_H
#define REGEXALTERNATIVES_H

#include "regex.h"
#include <deque>
#include "regexcontainer.h"
#include "../iterator/iteratorpermuter.h"
#include <librexgen/simplestring.h>

class RegexAlternatives : public RegexContainer
{
public:
  RegexAlternatives(): RegexContainer(), groupId(-1) {}
  inline void addRegex(Regex *regex) { getChildren()->push_front(regex); }
  
  virtual inline const char* getXmlTag() const { return "alternative"; } 
  RegexType getRegexType() const { return Alternative; }
  
  int getMaxSize() const;
  
  Iterator* iterator(IteratorState* state) const;
  
  Iterator* singleIterator(IteratorState* state) const;
  
  Iterator* getContainerIterator();
  
  int getGroupId() const { return groupId; }
  void setGroupId (int _id) { groupId = _id; }
private:
  int groupId;
};

#endif // REGEXALTERNATIVES_H
