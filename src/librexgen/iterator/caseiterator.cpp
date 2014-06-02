/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2014  Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/iterator/caseiterator.h>

CaseIterator::CaseIterator(Iterator* __child)
	: Iterator(-1), child(__child), word(NULL), length(0), childHasNext(false) {
}

CaseIterator::~CaseIterator() {
	delete child;
	delete word;
}

void CaseIterator::readNextFromChild() {
	word.clear();

	childHasNext = child->next();
	child->value(word);
	for(int n=0; n<length; ++n) {
		if (uchar_isascii(str[n])) {
			codepoint_to_uchar(&word[n], tolower(str[n].character.ansi.value), str[n].encoding);
		} else {
			word[n] = str[n];
		}
	}
}

bool CaseIterator::next() {
	if (word == NULL) {
		childHasNext = readNextFromChild();

	}

	for (int idx=0; idx<length; ++idx) {
		
		if (! uchar_isascii(word[n])) {
			continue;
		}

		if (islower(word[n].character.ansi.value)) {
			word[n].character.ansi.value = toupper(word[n].character.ansi.value);
			return childNasNext;
		}

		if (isupper(word[n].character.ansi.value) {
			word[n].character.ansi.value = tolower(word[n].character.ansi.value);
		}
	}
	return childHasNext;
}

void CaseIterator::value(SimpleString& dst) const {
	for (int n=0; n<length; ++n) {
		dst.push_back(word[n]);
	}
}
