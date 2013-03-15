/*
    Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <librexgen/regex/classregex.h>
#include <algorithm>
#include <vector>

void ClassRegex::addCharacter(char_type ch, bool ignoreCase) {
  characters.push_back(ch);
  if (ignoreCase && islower(ch)) {
    characters.push_back(toupper(ch));
  }
}
void ClassRegex::addRange(char_type a, char_type b, bool ignoreCase) {
  while (a <= b) {
    char_type ch = a++;
    characters.push_back(ch);
    if (ignoreCase && islower(ch)) {
      characters.push_back(toupper(ch));
    }
  }
}

int ClassRegex::appendContent(char_type* dst, size_t size, int level) const {
  int l, length = 0;
  auto iter = characters.begin();

  l = appendSpace(dst, size, level);
  length += l;
  if ((size -= l) < 0) goto finish;
  dst += l;
  while (iter != characters.end() && size > 2) {
    *dst++ = *iter++;
    --size;
    ++length;
  }
#if defined(_WIN32) && defined(UNICODE) && defined(_UNICODE)
  l = utf_snprintf(dst, size, _T("\n"));
#else
  l = utf_snprintf(dst, size, "\n");
#endif
  length += min(l, static_cast<int>(size));
  finish:
  return length;
}

Iterator* ClassRegex::iterator(IteratorState* state) const {
  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return new ClassRegexIterator(
      getId(), &characters[0], characters.size());
  } else {
    return new IteratorPermuter(
      getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}

