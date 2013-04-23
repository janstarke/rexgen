/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2013  Jan Starke <jan.starke@outofbed.org>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef STREAMREGEXITERATOR_H
#define STREAMREGEXITERATOR_H

#include <librexgen/iterator/iterator.h>


class StreamRegexIterator : public Iterator
{
public:
    StreamRegexIterator(int _id, FILE* in)
      : Iterator(_id), infile(in) {state = resetted; readNextWord();}
    bool next() {
      const bool res = (state == resetted);
      state = usable;
      return res;
    }
    bool forceNext() {
      readNextWord();
      return __hasNext;      
    }
    bool hasNext() const { return state == resetted; }
    void value(SimpleString& dst) const {
      dst.append(buffer);
    }
    //void reset() {}
private:
  void readNextWord() {
    if (feof(infile)) {
      __hasNext = false;
    } else {
      if (nullptr == fgets(buffer, sizeof(buffer)/sizeof(buffer[0])-1, infile)) {
        __hasNext = false;
      } else {
        __hasNext = true;
        unsigned int idx = 0;
        while (idx < sizeof(buffer)/sizeof(buffer[0])-2
                    && buffer[idx] != '\r'
                    && buffer[idx] != '\n') { ++idx; }
        buffer[idx] = 0;
      }
    }
  }
  
  FILE* infile;
  char buffer[4096];
  bool __hasNext;
};

#endif // STREAMREGEXITERATOR_H
