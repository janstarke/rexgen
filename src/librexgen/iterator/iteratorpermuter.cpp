/*
    Copyright (C) 2012-2013  Jan Starke <rexgen@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
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
}

void IteratorPermuter::value(SimpleString& dst) const
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
