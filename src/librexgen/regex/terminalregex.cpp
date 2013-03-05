/*
 *  Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 * Neither the name of the <organization> nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
 *  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <librexgen/regex/terminalregex.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/unicode.h>

void TerminalRegex::prependSingleCharacter(const char_type* v) {
  char_type* tmp = value;
  ssize_t size =        1               /* the new character */
                  +     utf_strlen(tmp) /* the old value */
                  +     1;              /* the trailing null byte */
  value = new char_type[size];
  value[0] = parseFirstCharacter(v);
  utf_strncpy(&value[1], tmp, size-1);
  delete tmp;
}

void TerminalRegex::setValue(const char_type* v) {
  delete value;
  ssize_t size = utf_strlen(v)+1;
  value = new char_type[size];
  utf_strncpy(value, v, size);
}

int TerminalRegex::appendContent(
    char_type* dst, ssize_t size, int level) const {
  int l, length = 0;
  const char* format = PRINTF_FORMAT "\n";
  l = appendSpace(dst, size, level);
  length += l;
  if ((size -= l) < 0) goto finish;
  dst += l;

  length += utf_snprintf(dst, size, format, value);
  finish:
  return length;
}

Iterator* TerminalRegex::iterator(IteratorState* state) const {
  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return new TerminalRegexIterator(getId(), value);
  } else {
    return new IteratorPermuter(
      getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}
