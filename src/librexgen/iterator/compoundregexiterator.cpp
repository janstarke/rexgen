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

CompoundRegexIterator::CompoundRegexIterator(int _id)
  : Iterator(_id) {
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    i->reset();
    i->next();
  });
}

void CompoundRegexIterator::reset() {
  Iterator::reset();
  for_each(iterators.begin(), iterators.end(), [](Iterator* i) {
    i->reset();
  });
  state = resetted;
}

bool CompoundRegexIterator::next() {
  state = usable;
  if (state == resetted) { return true; }
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
  iterators.push_back(i);
}


