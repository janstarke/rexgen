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


#include "terminalregexiterator.h"
#include <assert.h>
#include <algorithm>
#include "../debug.h"
#include "../unicode.h"

TerminalRegexIterator::TerminalRegexIterator(int _id, const char_type* _terminal)
: Iterator(_id), terminal(_terminal)
{
  terminal_length = utf_strlen(_terminal);
  assert (! canUseValue());
  assert (hasNext());
} 

int TerminalRegexIterator::value(char_type* dst, ssize_t size) const
{
  assert(canUseValue());
  utf_strncpy(dst, terminal, size);
  return std::min(size-1, terminal_length);
}

void TerminalRegexIterator::next()
{
  ENTER_METHOD;
  //assert( hasNext() );
  Iterator::next();
  if (state == resetted)
    state = usable;
  else
    state = not_usable;
  assert(canUseValue());
  LEAVE_METHOD;
}

bool TerminalRegexIterator::hasNext() const
{
  ENTER_METHOD;
  RETURN (state == resetted);
}

void TerminalRegexIterator::reset()
{
    Iterator::reset();
    state = resetted;
    assert(! canUseValue());
}

int TerminalRegexIterator::toString(char_type* dst, ssize_t size) const
{
  return utf_snprintf(dst, size, "TerminalRegexIterator %d (value = '%s')",
	       getId(),
	       terminal);
}
