/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2015  Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/regex/streamregex.h>
#include <librexgen/genericerror.h>

#include <unistd.h>
#include <cstdio>
using namespace std;

StreamRegex::StreamRegex(callback_fp cb)
  : callback(cb) {
  /* this will not be deleted here, but in the iterator tree */
  iter = new StreamRegexIterator(getId(), callback);
}

Iterator* StreamRegex::iterator(IteratorState* state) const {
  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return singleIterator(state);
  } else {
    return new IteratorPermuter(
             getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}

Iterator* StreamRegex::singleIterator(IteratorState* state) const {
  state->setStreamIterator(iter);
  return iter;
}

unsigned long long int StreamRegex::size() const {
  /* files with more than 2^32 newlines do not make sense to be handled */
  size_t __size = 0;

  /* loop through file, inspired by http://blog.fefe.de/?ts=aa3c0cd3 */
  while (NULL != callback()) {
    ++__size;
  }
  return __size;
}

