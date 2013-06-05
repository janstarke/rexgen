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


#ifndef STREAMREGEX_H
#define STREAMREGEX_H

#include <librexgen/regex/regex.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/iterator/streamregexiterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/stacktrace.h>
#include <cstdio>


class StreamRegex : public Regex
{

public:
    Iterator* iterator(IteratorState* state) const {
      if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
        return singleIterator(state);
      } else {
        return new IteratorPermuter(
          getId(), this, state, getMinOccurs(), getMaxOccurs());
      }
    }
    Iterator* singleIterator(IteratorState* state) const {
      state->setStreamIterator(iter);
      return iter;
    }
    void appendContent(SimpleString& /* dst */, int /* level */) const {}
    RegexType getRegexType() const { return Stream; }
    const char* getXmlTag() const { return "stream"; }
    StreamRegex(FILE* in)
      : infile(in) {
        /* this will not be deleted here, but in the iterator tree */
        iter = new StreamRegexIterator(getId(), infile);
      }
    
private:
  FILE* infile;
  StreamRegexIterator* iter;
};

#endif // STREAMREGEX_H
