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

#include <librexgen/iterator/regexalternativesiterator.h>
#include <librexgen/debug.h>
#include <librexgen/unicode.h>
#include <assert.h>
#include <cstring>
#include <deque>
#include <vector>

RegexAlternativesIterator::RegexAlternativesIterator(int _id)
  : Iterator(_id), iter(iterators.begin()) {
  state = resetted;
}


void RegexAlternativesIterator::reset() {
  ENTER_METHOD;
  Iterator::reset();
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    i->reset();
  });
  iter = iterators.begin();
  state = resetted;
  LEAVE_METHOD;
}

void RegexAlternativesIterator::value(SimpleString& dst) const {
  ENTER_METHOD;
  /*
  assert(canUseValue());
  assert(iter != iterators.end());
  */
  (*iter)->value(dst);
  LEAVE_METHOD;
}


bool RegexAlternativesIterator::next() {
  ENTER_METHOD;

  if (state == resetted) {
    state = usable;
    RETURN(true);
  }

  if ((*iter)->next()) {
    return true;
  }
  ++iter;
  if (iter == iterators.end()) {
    iter = iterators.begin();
    return false;
  }
  (*iter)->next();
  RETURN (true);
}

bool RegexAlternativesIterator::hasNext() const {
  ENTER_METHOD;
  if (iterators.size() == 0 || state == not_usable) {
    /* if we don't have any iterator, you cannot call next() */
    RETURN(false);
  }

  if (state == resetted) {
    /* we can return true here,
     * because we know that we have at least one iterator
     */
    RETURN(true);
  }

  if (iter == iterators.end()) {
    RETURN(false);
  }

  if ((*iter)->hasNext()) {
    RETURN(true);
  } else {
    deque<Iterator*>::iterator tmp = iter;
    ++tmp;
    RETURN(tmp != iterators.end());
  }
}

void RegexAlternativesIterator::addChild(Iterator* i) {
  ENTER_METHOD;
  iterators.push_back(i);
  iter = iterators.begin();
  i->next();
  LEAVE_METHOD;
}

bool RegexAlternativesIterator::canUseValue() const {
  if (!Iterator::canUseValue()) {
    return false;
  }
  if (iter == iterators.end()) {
    return false;
  }
  return ((*iter)->canUseValue());
}

