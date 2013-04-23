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

#ifndef ITERATORSTATE_H
#define ITERATORSTATE_H

#include <map>
#include <algorithm>
#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/streamregexiterator.h>

using namespace std;

class IteratorState
{
public:
  
  void registerIterator(int id, const Iterator* iterator) {
    groupIterators[id] = iterator;
  }
  
  const Iterator* getIterator(int id) const {
    if (id == -1) {
      return getStreamIterator();
    } else {
      return groupIterators.at(id);
    }
  }
  
  void setRandomize(bool rnd) { randomize = rnd; }
  bool getRandomize() const { return randomize; }
  
  void setStreamIterator(StreamRegexIterator* iter) {streamIterator = iter;}
  StreamRegexIterator* getStreamIterator() const { return streamIterator; }
  
private:
  map<int, const Iterator*> groupIterators;
  bool randomize = false;
  StreamRegexIterator* streamIterator = nullptr;
};

#endif // ITERATORSTATE_H
