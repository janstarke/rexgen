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

#ifndef SRC_LIBREXGEN_REGEX_REGEX_H_
#define SRC_LIBREXGEN_REGEX_REGEX_H_

#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/regex/quantifier.h>
#include <librexgen/iterator/iterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/debug.h>
#include <iostream>

typedef enum {
  Compound,
  Alternative,
  Terminal,
  Class,
  Reference,
  Stream,
  Range
} RegexType;

class IteratorState;

class Regex  {
 public:
  Regex() : quantifier(1, 1) {id = createId();}
  virtual ~Regex() {}

  inline unsigned int getMinOccurs() const { return quantifier.getMin(); }
  inline unsigned int getMaxOccurs() const { return quantifier.getMax(); }

  inline void setMinOccurs(unsigned int _min) { quantifier.setMin(_min); }
  inline void setMaxOccurs(unsigned int _max) { quantifier.setMax(_max); }

  inline void setQuantifier(const Quantifier& q) { quantifier = q; }

  virtual RegexType getRegexType() const = 0;

  virtual Iterator* iterator(IteratorState* state) const {
    if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
      return singleIterator(state);
    } else {
      return new IteratorPermuter(
               getId(), this, state, getMinOccurs(), getMaxOccurs());
    }
  }
  virtual Iterator* singleIterator(IteratorState* state) const = 0;

  int getId() const { return id; }

  virtual int getGroupId() const { return -1; }

  virtual bool usesCallback() const { return false; }

 protected:
  virtual int createId() {
    return ++next_id;
  }

 private:
  Quantifier quantifier;
  static int next_id;
  int id;
};

#endif  // SRC_LIBREXGEN_REGEX_REGEX_H_

