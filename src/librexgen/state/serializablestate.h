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

#ifndef SERIALIZABLESTATE_H
#define SERIALIZABLESTATE_H

#ifdef __cplusplus
#include <vector>
#include <map>
#include <stdint.h>

using namespace std;

class SerializableState
{
public:
  typedef int32_t stateword_t;
  SerializableState(stateword_t id);
  SerializableState(const stateword_t* vptr, size_t& words);
  ~SerializableState();
  void serialize(vector<stateword_t>* dst) const;
  int getIteratorId() const { return iterator_id; }
  void setIteratorId(stateword_t id) { iterator_id = id; }
  
  void addValue(stateword_t value);
  void addValue(const SerializableState* state);
  stateword_t getValue(int idx) const;
  const SerializableState* getChildState(int id) const;
  int getValuesCount() const;
  int getChildStatesCount() const;
private:
  stateword_t iterator_id;
  vector<stateword_t> values;
  map<int, const SerializableState*> childStates;
};

#endif /* __cplusplus */

#endif /* SERIALIZABLESTATE_H */
