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
	: Iterator(-1), child(__child) {
}

CaseIterator::~CaseIterator() {
	delete child;
}

bool CaseIterator::readNextFromChild() {
	word.clear();
	const bool childHasNext = child->next();
	child->value(word);
	for(unsigned int n=0; n<word.size(); ++n) {
		word.tolower(n);
	}
	return childHasNext;
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
		return (word.size() > 0);
	}

	unsigned int n;
	for (n=0; n<word.size(); ++n) {
		if (word.islower(n)) {
			word.toupper(n);
			break;
		}
		word.tolower(n);
	}

	if (n<word.size()) { return true; }
	return readNextFromChild();
}

void CaseIterator::value(SimpleString& dst) const {
	for (unsigned int n=0; n<word.size(); ++n) {
		dst.push_back(word[n]);
	}
}
