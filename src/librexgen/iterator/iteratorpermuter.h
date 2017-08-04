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


#ifndef SRC_LIBREXGEN_ITERATOR_ITERATORPERMUTER_H_
#define SRC_LIBREXGEN_ITERATOR_ITERATORPERMUTER_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/iterator/iteratorcontainer.h>

class Regex;

class IteratorPermuter : public IteratorContainer {
 public:
  void value(SimpleString* dst) const;
  bool hasNext() const;
  IteratorPermuter(int _id, const Regex* re, IteratorState* is,
                   unsigned int min, unsigned int max);
  ~IteratorPermuter();
  bool next();
  void init();

  /**
   * returns the number of elements created by this iterator
   */
  // uint64_t size() const;
 private:
  bool existsIteratorWithNextElement() const;

  const unsigned int min_occurs, max_occurs;
  const Regex* regex;
  bool hasNextElement;

  unsigned int current;
  unsigned int occurs;
};


#endif  // SRC_LIBREXGEN_ITERATOR_ITERATORPERMUTER_H_
