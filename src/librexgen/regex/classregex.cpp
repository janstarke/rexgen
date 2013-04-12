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
#include <librexgen/unicode/uchar.h>
#include <algorithm>
#include <vector>

bool ClassRegex::contains(const uchar_t& ch) const
{
  for (auto iter = characters.cbegin(); iter != characters.cend(); ++iter) {
    if ((*iter).codepoint == ch.codepoint) {
      return true;
    }
  }
  return false;
}

void ClassRegex::__append_character(const uchar_t& ch)
{
  if (! contains(ch)) {
    characters.push_back(ch);
  }
}
void ClassRegex::__insert_character(const uchar_t& ch)
{
  if (! contains(ch)) {
    characters.insert(characters.begin(), ch);
  }
}

void ClassRegex::addCharacter(const uchar_t& ch, bool ignoreCase) {
  __insert_character(ch);
  if (ignoreCase && uchar_isascii(ch)) {
    uchar_t uch;
    
    if (islower(ch.character.ansi.value)) {
      codepoint_to_uchar(&uch, toupper(ch.character.ansi.value), encoding);
      __insert_character(uch);
    } 
    
    else if (isupper(ch.character.ansi.value)) {
      codepoint_to_uchar(&uch, tolower(ch.character.ansi.value), encoding);
      __insert_character(uch);
    }
  }
}
void ClassRegex::addRange(const uchar_t& uch_a, const uchar_t& uch_b, bool ignoreCase) {
  uint16_t a = uch_a.codepoint;
  while (a <= uch_b.codepoint) {
    uchar_t ch;
    uchar_t uch;
    codepoint_to_uchar(&ch, a++, uch_a.variant);
    characters.push_back(ch);
    
    if (ignoreCase && uchar_isascii(ch)) {
      if (islower(ch.character.ansi.value)) {
        codepoint_to_uchar(&uch, toupper(ch.character.ansi.value), encoding);
        __append_character(uch);
      }
      
      else if (isupper(ch.character.ansi.value)) {
        codepoint_to_uchar(&uch, tolower(ch.character.ansi.value), encoding);
        __append_character(uch);
      }
    }
  }
}

int ClassRegex::appendContent(char_type* dst, size_t size, int level) const {
  size_t l, length = 0;
  auto iter = characters.begin();

  l = appendSpace(dst, size, level);
  if (size <= l) goto finish;
  length += l;
  size -= l;
  dst += l;
  while (iter != characters.end() && size > 2) {
    *dst++ = (*iter).character.ansi.value;
    ++iter;
    --size;
    ++length;
  }
#if defined(_WIN32) && defined(UNICODE) && defined(_UNICODE)
  l = utf_snprintf(dst, size, _T("\n"));
#else
  l = utf_snprintf(dst, size, "\n");
#endif
  length += min(l, size);
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

