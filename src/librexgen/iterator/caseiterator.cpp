/*
  rexgen - a tool to create words based on regular expressions
  Copyright (C) 2012-2015  Jan Starke <jan.starke@outofbed.org>

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
#include <librexgen/parser/group_options.h>
#include <librexgen/common/ntz.h>
#include <librexgen/string/uchar.h>

CaseIterator::CaseIterator(Iterator* __child, int options)
  : IteratorContainer(-1), child(__child), handle_case(options), max(-1) {
}

CaseIterator::~CaseIterator() {
  delete child;
}

bool CaseIterator::readNextFromChild() {
  //fprintf(stderr, "readNextFromChild()\n");

  /* clear the previously read word
   * and the information about foldable characters */
  word.clear();
  changeable_characters.clear();

  /* read next word */
  const bool childHasNext = child->next();
  child->value(word);

  for(unsigned int n=0; n<word.size(); ++n) {
    if (UCHAR_CAN_CHANGE_CASE(word[n])) {
      word.tolower(n);
      changeable_characters.push_back(n);
    }
  }

  //fprintf(stderr, ">>> found %d changeable characters\n", changeable_characters.size());

  /* the fast version of next() uses the counter k,
   * so it can only be used with strings of limited length */
  if (changeable_characters.size() <= max_fast_character_bytes) {
    max = 1 << changeable_characters.size();
    k = max;
  } else {
  }
  parity = 0;

  return childHasNext;
}

bool CaseIterator::hasNext() const {
  if (word.size() == 0) {
    return child->hasNext();
  }
  return true;
}

/* wrapper function for the simple and the standard version of next() */
bool CaseIterator::next() {
  //fprintf(stderr, "next()\n");
  if (word.size() == 0) {
    readNextFromChild();

    /* keep in mind: k is the number of remaining variants */
    return (word.size() > 0 && k > 1);
  }

  /* delete UCHAR_FLAGS_CAN_CHANGE_CASE for all characters */
  if (handle_case == CASE_PRESERVE) {
    for (unsigned int n=0; n<word.size(); ++n) {
			UCHAR_SET_PRESERVE_CASE(word[n]);
    }
  }

  return fast_next() && (k>1);
}

/* this function is inspired by the algorithm for Grey binary generation
 * of Donald Ervin Knuth, found in TAOCP, 7.2.1.1 */
bool CaseIterator::fast_next() {
  //fprintf(stderr, "fastNext()\n");
  --k;
  /* omit step G1, this is done in readNextFromChild() */

  /* don't know what G2 should do :-( */
  unsigned int j=0;

  /* G4:
   * if (parity_n+1 == 0) set j <- ntz(k)
	 * ntz() does the same as the ruler function p(k) in eq. 7.1-(00)
   */
	//fprintf(stderr, "ntz(k=%016x) <= %d\n", k, ntz(k));
  j = ntz(k) & (parity);
        
  /* G3: invert parity */
  /* we need the inverted value of parity for the fast calculation
   * of j, so we swapped the two steps. Note that the following
   * precondition holds, after G4 and G3:
   * if (parity == 0) { j = ntz(k); }
   */
  parity ^= (unsigned int) -1;

  /* G5 */
  //fprintf(stderr, "p=%d, k = 0x%08x, j = %d\n", parity, k, j);
  assert(j < changeable_characters.size());
  uchar_toggle_case(word[changeable_characters[j]]);

  return (k != (counter_t)-1);
}

void CaseIterator::value(SimpleString& dst) const {
  //fprintf(stderr, "value()\n");
  for (unsigned int n=0; n<word.size(); ++n) {
    dst.push_back(word.getAt(n));
  }
}
