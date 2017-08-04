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

#include <librexgen/regex/streamregex.h>


StreamRegex::StreamRegex(callback_fp_mb cb)
  : callback(cb) {
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
  StreamRegexIterator* iter = state->getStreamIterator();
  if (iter == NULL) {
    iter = new StreamRegexIterator(getId(), callback);
    state->setStreamIterator(iter);
  }
  return iter;
}
