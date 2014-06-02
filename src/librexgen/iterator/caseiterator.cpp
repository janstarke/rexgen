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
	: Iterator(-1), child(__child), childHasNext(false) {
}

CaseIterator::~CaseIterator() {
	delete child;
}

void CaseIterator::readNextFromChild() {
	word.clear();

	childHasNext = child->next();
	child->value(word);
	for(unsigned int n=0; n<word.size(); ++n) {
		word.tolower(n);
	}
}

bool CaseIterator::hasNext() const {
	if (word.size() == 0) {
		return child->hasNext();
	}
	return true;
}

bool CaseIterator::next() {
	if (word.size() == 0) {
		readNextFromChild();
	}

	for (unsigned int n=0; n<word.size(); ++n) {
		
		if (word.islower(n)) {
			word.toupper(n);
			return childHasNext;
		}

		word.tolower(n);
	}
	return childHasNext;
}

void CaseIterator::value(SimpleString& dst) const {
	for (unsigned int n=0; n<word.size(); ++n) {
		dst.push_back(word[n]);
	}
}
