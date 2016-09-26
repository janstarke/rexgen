/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

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

#ifndef __regexcontainer_h__
#define __regexcontainer_h__

#include <deque>
#include <algorithm>
#include <functional>
#include <librexgen/regex/regex.h>
#include <librexgen/debug.h>
#include <librexgen/string/simplestring.h>

using namespace std;

class RegexContainer : public Regex {
 public:

  void mapToChildren(function<void (const Regex*)> fct) const {
    for (auto r : regexObjects) {
      fct(r);
    }
  }

  void mapToChildren(function<void (const Regex*)> fct) {
    for (auto r : regexObjects) {
      fct(r);
    }
  }

  virtual ~RegexContainer() {
    mapToChildren([](const Regex* re) {delete re;});
		regexObjects.clear();
  }

  virtual bool usesCallback() const {
    for (auto re: regexObjects) {
      if (re->usesCallback()) {
        return true;
      }
    }
    return Regex::usesCallback();
  }

protected:
  size_t children() const { return regexObjects.size(); }

  deque<Regex*>* getChildren() { return &regexObjects; }
        Regex* firstChild()       {return regexObjects[0];}
  const Regex* firstChild() const {return regexObjects[0];}

  void push_front(Regex* re) {regexObjects.push_front(re);}
  void push_back(Regex* re) {regexObjects.push_back(re);}

private:
  deque<Regex*> regexObjects;
};

#endif
