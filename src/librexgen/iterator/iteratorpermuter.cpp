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

#include "iteratorpermuter.h"
#include <algorithm>
#include "../debug.h"
#include "../unicode.h"
#include <librexgen/iterator/iteratorstate.h>

using namespace std;

IteratorPermuter::IteratorPermuter(int _id, const Regex* re, IteratorState* is, unsigned int min, unsigned int max)
  : Iterator(_id), min_occurs(min), max_occurs(max), regex(re), iteratorState(is) {
  initIterators();
  state = resetted;
}

int IteratorPermuter::value(char_type* dst, ssize_t size) const {
  ENTER_METHOD;
  assert(canUseValue());
  int length = 0;

  /* handle optional values, such as ab{0,1}c */
  if (iterators.size() == 0) {
    *dst = 0;
    RETURN(0);
  }

  for (auto i = iterators.cbegin(); i!=iterators.cend(); ++i) {
    int l = (*i)->value(dst, size);
    dst += l;
    size -= l;
    length += l;
  }
  RETURN(length);
}

bool IteratorPermuter::hasNext() const {
  ENTER_METHOD;

  if (state == resetted) {
    RETURN(true);
  }

  if (iterators.size() < max_occurs) {
    RETURN(true);
  }

  RETURN(existsIteratorWithNextElement());
}


void IteratorPermuter::next() {
  ENTER_METHOD;
  //assert( hasNext() );

  Iterator::next();

  if (! existsIteratorWithNextElement()) {
    /* handle optional values, such as ab{0,1}c */
    if (state == resetted && iterators.size()==0) {
      state = usable;
      LEAVE_METHOD;
    }

    for_each(iterators.begin(), iterators.end(),[](Iterator* i) {
      i->reset();
    });
    Iterator* i = regex->singleIterator(iteratorState);
    iterators.push_front(i);
    state = resetted;
  }


  if (state == resetted) {
    state = usable;
    for_each (iterators.begin(), iterators.end(),
    [&state](Iterator* i) {
      if (i->hasNext()) {
        i->next();
      } else {
        state = not_usable;
      }
    });
    LEAVE_METHOD;
  }

  for(auto i=iterators.begin(); i!=iterators.end(); ++i) {
    if ((*i)->hasNext()) {
      (*i)->next();
      assert((*i)->canUseValue());
      break;
    } else {
      (*i)->reset();
      initSingleIterator(*i);
    }
  }

  assert(canUseValue());

  TRACE_INT("next2: current length: %d", iterators.size());
  LEAVE_METHOD;
}

void IteratorPermuter::reset() {
  ENTER_METHOD;
  Iterator::reset();
  initIterators();
  state = resetted;
  LEAVE_METHOD;
}

void IteratorPermuter::initIterators() {
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    delete i;
  });
  iterators.clear();
  for (unsigned int n=0; n<min_occurs; ++n) {
    Iterator* i = regex->singleIterator(iteratorState);
    iterators.push_front(i);
  }
}

void IteratorPermuter::initSingleIterator(Iterator* iter) {
  if (! iter->canUseValue()) {
    assert(iter->hasNext());
    if (iter->hasNext()) {
      iter->next();
    }
  }
  assert(iter->canUseValue());
}

bool IteratorPermuter::existsIteratorWithNextElement() const {
  ENTER_METHOD;
  for(auto i=iterators.cbegin(); i!=iterators.cend(); ++i) {
    if ((*i)->hasNext()) {
      RETURN( true );
    }
  }
  RETURN(false);
}


int IteratorPermuter::toString(char_type* dst, ssize_t size) const {
  return utf_snprintf(dst, size, "IteratorPermuter %d (min=%d, max=%d, current=%d)",
                      getId(),
                      min_occurs,
                      max_occurs,
                      iterators.size());
}
