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
#include "debug.h"
#include "unicode.h"

using namespace std;

IteratorPermuter::IteratorPermuter(int _id, const Regex* re, unsigned int min, unsigned int max)
      : Iterator(_id), min_occurs(min), max_occurs(max), regex(re), state(resetted)
{
  for (unsigned int n=0; n<min; ++n) {
    iterators.push_back(re->singleIterator());
  }
}

int IteratorPermuter::value(char_type* dst, ssize_t size) const
{
  ENTER_METHOD;
  assert(canUseValue());
  int length = 0;
  for_each(iterators.cbegin(), iterators.cend(),
   [&length, &dst, &size](const Iterator* i){
      int l = i->value(dst, size);
      dst += l;
      size -= l;
      length += l;
  });
  RETURN(length);
}

bool IteratorPermuter::hasNext() const
{
  ENTER_METHOD;
  
  if (state == resetted) {
    RETURN(true);
  }
  
  if (iterators.size() < max_occurs) {
    RETURN(true);
  }
  
  RETURN(existsIteratorWithNextElement());
}


void IteratorPermuter::next()
{
  ENTER_METHOD;
  
  if (! existsIteratorWithNextElement()) {
    if (iterators.size() >= max_occurs) { LEAVE_METHOD; }
  }
  
  Iterator::next();
  
  if (state == resetted) {
    state = usable;
  }
  
  if (! existsIteratorWithNextElement()) {
    for_each(iterators.begin(), iterators.end(),[](Iterator* i){i->reset();});
    iterators.push_front(regex->singleIterator());
  }
  
  bool found_next = false;
  for(auto i=iterators.begin(); i!=iterators.end(); ++i)
  {
    if (! (*i)->canUseValue()) {
      if ((*i)->hasNext()) (*i)->next();
      assert((*i)->canUseValue());
    }
    
    if (found_next) {
      if (!(*i)->canUseValue()) {
	if ((*i)->hasNext()) (*i)->next();
      }
      continue;
    }
    
    if ((*i)->hasNext()) {
      (*i)->next();
      found_next = true;
      assert((*i)->canUseValue());
    } else {
      (*i)->reset();
      if ((*i)->hasNext()) { (*i)->next(); }
      assert((*i)->canUseValue());
    }
  }
  LEAVE_METHOD;
}

void IteratorPermuter::reset()
{
  ENTER_METHOD;
  for_each(iterators.begin(), iterators.end(), [](Iterator* i){delete i;});
  iterators.clear();
  for (unsigned int n=0; n<min_occurs; ++n) {
    iterators.push_front(regex->singleIterator());
  }
  state = resetted;
  LEAVE_METHOD;
}

