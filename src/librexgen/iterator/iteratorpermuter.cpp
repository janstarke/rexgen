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

#include <librexgen/iterator/iteratorpermuter.h>

IteratorPermuter::IteratorPermuter(int _id, const Regex* re, IteratorState* is, unsigned int min, unsigned int max)
: Iterator(_id), min_occurs(min), max_occurs(max), regex(re), iteratorState(is),
hasNextElement(true), occurs(min_occurs)
{
  for (unsigned int n=0; n<max_occurs; ++n) {
    iterators.push_back(regex->singleIterator(iteratorState));
  }
  current = 0;
  state = resetted;
}

void IteratorPermuter::value(string_type& dst) const
{
  ENTER_METHOD;
  for (unsigned int n=0; n<occurs; ++n) {
    iterators[n]->value(dst);
  }
  LEAVE_METHOD;
}

bool IteratorPermuter::hasNext() const
{
  ENTER_METHOD;
  
  if (state == resetted) {
    RETURN(true);
  }
  
  if (occurs < max_occurs) {
    RETURN(true);
  }
  
  RETURN(hasNextElement);
}

void IteratorPermuter::next()
{
  ENTER_METHOD;
  
  if (state == resetted) {
    bool has_next = false;
    for_each(iterators.begin(), iterators.end(), [&has_next](Iterator* i) {i->next();has_next |= i->hasNext();});
    hasNextElement = has_next;
    state = usable;
    LEAVE_METHOD;
  } else if (state == usable && occurs == 0) {
    if (occurs < max_occurs) {
      ++occurs;
      current = 0;
    } else {
      state = not_usable;
    }
    LEAVE_METHOD;
  }
  
  hasNextElement = (occurs < max_occurs);

  if (iterators[current]->hasNext()) {
    iterators[current]->next();
    if (current != 0) {
      hasNextElement = true;
    } else {
      if (! hasNextElement) {
        hasNextElement = existsIteratorWithNextElement();
      }
    }
    state = usable;
    LEAVE_METHOD;
  }
  
  /* find some iterator with a next element */
  while(current < occurs) {
    if (iterators[current]->hasNext()) {
      break;
    }
    ++current;
  }
  if (current >= occurs) { /* we must switch to the next length (if allowed) */
    assert (current == occurs);
    if (occurs >= max_occurs) { /* no more elements left */
      state = not_usable; LEAVE_METHOD;
    }
    hasNextElement = iterators[occurs]->hasNext();
    ++occurs;
  } else { /* select next element */
    iterators[current]->next();
  }
  
  /* reset all iterators left to the current one */
  while(current > 0) {
    --current;
    iterators[current]->reset();
    iterators[current]->next();
    hasNextElement |= iterators[current]->hasNext();;
  }
  
  assert(canUseValue());
  
  TRACE_INT("next2: current length: %d", (int)occurs);
  LEAVE_METHOD;
}

void IteratorPermuter::reset()
{
  ENTER_METHOD;
  Iterator::reset();
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {i->reset();});
  occurs = min_occurs;
  current = 0;
  state = resetted;
  hasNextElement = true;
  LEAVE_METHOD;
}

bool IteratorPermuter::existsIteratorWithNextElement() const
{
  ENTER_METHOD;
  for(auto i=iterators.cbegin(); i!=iterators.cend(); ++i) {
    if ((*i)->hasNext()) {
      RETURN( true );
    }
  }
  RETURN(false);
}

