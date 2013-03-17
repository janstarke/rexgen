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


#include <librexgen/iterator/compoundregexiterator.h>
#include <librexgen/debug.h>
#include <librexgen/unicode.h>
#include <assert.h>
#include <algorithm>

CompoundRegexIterator::CompoundRegexIterator(int _id)
  : Iterator(_id) {
}

void CompoundRegexIterator::reset() {
  Iterator::reset();
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    i->reset();
  });
  state = resetted;
}

void CompoundRegexIterator::next() {
  assert(hasNext());

  bool found_next = false;
  Iterator::next();
  state = not_usable;
  for (auto i = iterators.begin(); i != iterators.end(); ++i) {
    if ((*i)->canUseValue() && !found_next) {
      if ((*i)->hasNext()) {
        (*i)->next();
        found_next = true;
        state = usable;
      } else {
        (*i)->reset();
        if ((*i)->hasNext()) {
          (*i)->next();
          state = usable;
        }
      }
    } else if (!(*i)->canUseValue()) {
      if ((*i)->hasNext()) {
        (*i)->next();
        state = usable;
      }
    }
  }
}

void CompoundRegexIterator::value(string_type& dst) const {
  assert(canUseValue());
  for_each(iterators.begin(), iterators.end(),
  [&dst](Iterator* i) { i->value(dst); });
}

bool CompoundRegexIterator::hasNext() const {
  bool has_next = false;
  if (state == not_usable) {
    return false;
  }
  for_each(iterators.begin(), iterators.end(), [&has_next](Iterator* i) {
    has_next |= i->hasNext();
  });
  return has_next;
}

void CompoundRegexIterator::addChild(Iterator* i) {
  iterators.push_back(i);
}

Iterator::size_type CompoundRegexIterator::size() const {
  Iterator::size_type s = 0;
  for_each(iterators.begin(), iterators.end(), [&s](Iterator* i) {
    s *= i->size();
  });
  return s;
}


