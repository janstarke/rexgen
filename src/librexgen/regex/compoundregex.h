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


#ifndef COMPOUNDREGEX_H
#define COMPOUNDREGEX_H

#include "regex.h"
#include <deque>
#include "regexcontainer.h"
#include "../iterator/iteratorpermuter.h"
#include "../unicode.h"
#include <librexgen/simplestring.h>

using namespace std;

class CompoundRegex : public RegexContainer
{
public:
  
  virtual inline const char* getXmlTag() const { return "compound"; }
  
  void prependRegex(Regex* regex);
  void appendRegex(Regex* regex);
  void getRawValue(string& target);
  RegexType getRegexType() const { return Compound; }
  Iterator* iterator(IteratorState* state) const;
  
  Iterator* singleIterator(IteratorState* state) const;
};

#endif // COMPOUNDREGEX_H
