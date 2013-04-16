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


#include <librexgen/iterator/compoundregexiterator.h>
#include <librexgen/debug.h>
#include <librexgen/unicode.h>
#include <assert.h>
#include <algorithm>
#include <cstdlib>

CompoundRegexIterator::CompoundRegexIterator(int _id, bool rnd)
  : Iterator(_id), randomize(rnd) {
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    i->reset();
    i->next();
  });

  if (randomize) {
    for (unsigned int n = 0; n<iterators.size(); ++n) {
      rnd_iterators.push_back(n);
    }
    shuffle();
  }
}

void CompoundRegexIterator::reset() {
  Iterator::reset();
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    i->reset();
  });

  if (randomize) {
    shuffle();
  }
  state = resetted;
}

bool CompoundRegexIterator::next() {
  if (state == resetted) { state = usable; return true; }
  if (randomize) {
    for (auto rnd_i = rnd_iterators.begin(); rnd_i != rnd_iterators.end(); ++rnd_i) {
      if (iterators[*rnd_i]->next()) {
        return true;
      }
    }
    return false;
  }
  for (auto i = iterators.begin(); i != iterators.end(); ++i) {
    if ((*i)->next()) {
      return true;
    }
  }
  return false;
}

void CompoundRegexIterator::value(SimpleString& dst) const {
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
  rnd_iterators.push_back(iterators.size());
  if (randomize) {
    shuffle();
  }
  iterators.push_back(i);
  i->reset();
  i->next();
}



