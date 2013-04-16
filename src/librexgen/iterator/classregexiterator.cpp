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

#include <librexgen/iterator/classregexiterator.h>

ClassRegexIterator::ClassRegexIterator(
  int _id,
  const uchar_t* classcontent,
  size_t elements)
  :Iterator(_id) {
    buffer = new byte[elements*sizeof(char32_t)];
    buffer_length = 0;
    for (size_t n=0; n<elements; ++n) {
      byte* ptr = &buffer[buffer_length];
      buffer_length += uchar_to_utf(classcontent[n], ptr);
      ptrs.push_back(ptr);
      lengths.push_back(classcontent[n].char_length);
    }
    reset();
}

bool ClassRegexIterator::next() {
  if (state == resetted) {
    state = usable;
    return true;
  }
  ++current;
  if (current >= ptrs.size()) {
    current = 0;
    return false;
  }
  return true;
}