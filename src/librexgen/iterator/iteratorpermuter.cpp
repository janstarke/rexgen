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
  reset();
  __size = size();
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
  
  //RETURN(hasNextElement);
  RETURN(existsIteratorWithNextElement());
}

bool IteratorPermuter::next()
{
  ENTER_METHOD;
  
  /* special case handling for resetted state */
  if (state == resetted) { state = usable; RETURN(true); }
  
  /* special case handling for quantifier which starts with 0, i.e. {0,3} */
  if (state == usable && occurs == 0) { ++occurs; RETURN(true); }
  
  unsigned int n = 0;
  for (; n<occurs; ++n) { if (iterators[n]->next()) break; }
  if (n == max_occurs) { occurs = min_occurs; RETURN(false); }
  if (n == occurs)  { ++occurs; }
  RETURN(true);
}

void IteratorPermuter::reset()
{
  ENTER_METHOD;
  Iterator::reset();

  bool has_next = false;
  for_each(iterators.begin(), iterators.end(), [&has_next](Iterator* i) {i->next();has_next |= i->hasNext();});
  hasNextElement = has_next;

  occurs = min_occurs;
  current = 0;
  state = resetted;
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

Iterator::size_type IteratorPermuter::size() const {
  if (iterators.size() == 0) { return 0; }
  Iterator::size_type single_size = iterators[0]->size();
  Iterator::size_type s = 0;
  for (unsigned int e=min_occurs; e<=max_occurs; ++e) {
    s += _Pow_int(s, e);
  }
  return s;
}
