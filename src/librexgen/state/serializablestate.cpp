/*
 * rexgen - a tool to create words based on regular expressions
 * Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "serializablestate.h"
#include <algorithm>
#include <map>
#include <cstddef>

using std::size_t;

SerializableState::SerializableState(SerializableState::stateword_t id, stateword_t state) {
  iterator_id = id;
  stateEnum = state;
}

SerializableState::SerializableState(const SerializableState::stateword_t* vptr,
                                     size_t& words) {
  stateword_t size;
  words = 0;
  size_t consumed_words = 0;

  iterator_id = *vptr++;
  ++words;
  stateEnum = *vptr++;
  ++words;

  size = *vptr++;
  ++words;
  while (size > 0) {
    values.push_back(*vptr++);
    --size;
    ++words;
  }

  size = *vptr++;
  ++words;
  while (size > 0) {
    addValue(new SerializableState(vptr, consumed_words));
    --size;
    words += consumed_words;
    vptr += consumed_words;
  }
}

SerializableState::~SerializableState() {
  for (map<int, const SerializableState*>::iterator p=childStates.begin();
       p!=childStates.end(); ++p) {
    delete (*p).second;
  }
}

void SerializableState::addValue(SerializableState::stateword_t value) {
  values.push_back(value);
}

void SerializableState::addValue(const SerializableState* state) {
  childStates[state->getIteratorId()] = state;
}

SerializableState::stateword_t SerializableState::getValue(int idx) const {
  return values[idx];
}

const SerializableState* SerializableState::getChildState(int id) const {
  map<int, const SerializableState*>::const_iterator iter = childStates.find(id);
  if (iter != childStates.end()) {
    return iter->second;
  }
  return NULL;
}

size_t SerializableState::getValuesCount() const {
  return values.size();
}

size_t SerializableState::getChildStatesCount() const {
  return childStates.size();
}

void SerializableState::serialize(vector<stateword_t>* dst) const {
  /* iterator id */
  dst->push_back(iterator_id);
  /* state of the iterator (resetted, usable, etc) */
  dst->push_back(stateEnum);

  /* serialize integer values */
  dst->push_back(values.size());
  for (vector<stateword_t>::const_iterator v=values.begin(); v!=values.end();
       ++v) {
    dst->push_back(*v);
  }

  /* serialize child states */
  dst->push_back(childStates.size());
  for (map<int, const SerializableState*>::const_iterator p=childStates.begin();
       p!=childStates.end(); ++p) {
    (*p).second->serialize(dst);
  }
}

