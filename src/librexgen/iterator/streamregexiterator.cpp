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

#include <librexgen/iterator/streamregexiterator.h>
#include <stdlib.h>

void StreamRegexIterator::value(SimpleString* dst) const {

  if (callback_ctype == NULL) {
    /* we do not really which CTYPE we've stored or
     * which CTYPE we're required to create, so we
     * don't do character conversion
     */
    dst->append(&buffer[0], length);
  } else {
    /* we need to convert the characters */

    /* allocate temporary buffer; assume that one byte maps to one wide character */
    wchar_t *tmp = new wchar_t[(length + 1) * sizeof(wchar_t)];

    /* first, convert all characters to widechar */
    mbstowcs_l(tmp, &buffer[0], length + 1, callback_locale);

    /* next, convert widechar by widechar to the output encoding */
    wchar_t *ptr = tmp;
    while (*ptr != u'\0') {
      dst->append_widechar(*ptr);
      ptr++;
    }
  }
}

void StreamRegexIterator::readNextWord() {
  __hasNext = false;
  assert(callback != NULL);
  length = callback(&buffer[0], STREAMREGEXITERATOR_MAXLEN);
  if (length > 0) {
    __hasNext = true;
  }
}

SerializableState* StreamRegexIterator::getCurrentState() const {
  SerializableState* s = Iterator::getCurrentState();
  s->addValue(0);
  return s;
}

void StreamRegexIterator::setCurrentState(const SerializableState* s) {
  Iterator::setCurrentState(s);
  // fseek(infile, s->getValue(0), SEEK_SET);
}

