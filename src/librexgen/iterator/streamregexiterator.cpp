/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

    This program is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the Free
    Software Foundation; either version 2 of the License, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
    more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin St, Fifth Floor, Boston, MA 02110, USA
*/

#include <librexgen/iterator/streamregexiterator.h>
#include <cstdio>

using namespace std;

void StreamRegexIterator::readNextWord()
{
	__hasNext = false;
	if(infile != NULL) {
		if (! feof(infile)) {
			if (NULL == fgets(buffer, sizeof(buffer)/sizeof(buffer[0])-1, infile)) {
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
	} else if (callback != NULL) {
		const char *cp = callback();
		if (cp) {
			strncpy(buffer, cp, sizeof(buffer)-1);
			buffer[sizeof(buffer)-1] = 0;
			__hasNext = true;
		}
	}
}

SerializableState* StreamRegexIterator::getCurrentState() const
{
  SerializableState* s = Iterator::getCurrentState();
  const long pos = ftell(infile);
  s->addValue(pos);
  return s;
}

void StreamRegexIterator::setCurrentState(const SerializableState* s)
{
    Iterator::setCurrentState(s);
    fseek(infile, s->getValue(0), SEEK_SET);
}

