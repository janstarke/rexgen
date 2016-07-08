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
#include <librexgen/genericerror.h>

CaseIterator::CaseIterator(Iterator* __child, int options)
  : IteratorContainer(-1), child(__child), handle_case(options) {
}

CaseIterator::~CaseIterator() {
  if (child != NULL) {
		delete child;
	}
}

bool CaseIterator::readNextFromChild() {
  //fprintf(stderr, "readNextFromChild()\n");
  bool childHadNext;

  /* clear the previously read word
   * and the information about foldable characters */
  word.clear();
  changeable_characters.clear();

  /* read next word */
  childHadNext = child->next();
  child->value(word);

  for (unsigned int n=0; n<word.size(); ++n) {
    if (word.can_change_case(n)) {
      word.tolower(n);
      changeable_characters.push_back(n);
    }
  }

  if (changeable_characters.size() <= max_fast_character_bytes) {
    k = (1 << changeable_characters.size())-1;
  } else {
    assert(false);
    throw GenericError("cannot handle that much characters");
  }
  parity = 0;
  j = 0;      /* == ntz(k) & parity */

  /* delete UCHAR_FLAGS_CAN_CHANGE_CASE for all characters */
  if (handle_case == CASE_PRESERVE) {
		word.set_preserve_case();
  }

  return childHadNext;
}

bool CaseIterator::hasNext() const {
  if (word.size() == 0) {
    return child->hasNext();
  }
  return true;
}

/* this function is inspired by the algorithm for Grey binary generation
 * of Donald Ervin Knuth, found in TAOCP, 7.2.1.1 */
bool CaseIterator::next() {
  /* G1 */
  if (word.empty() || k == 0) {
    bool childHadNext = readNextFromChild();

    /* keep in mind: k is the number of remaining variants */
    //fprintf(stderr, "returning original value; k=%llu\n", k);
    return (childHadNext);
  }

  fast_next();
	return true;
}

inline void CaseIterator::fast_next() {
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

  /* G2: visit */

  //fprintf(stderr, "inverting at index %d\n", changeable_characters[j]);

  //assert(j < changeable_characters.size());
	word.toggle_case(changeable_characters[j]);
  --k;
}

void CaseIterator::value(SimpleString& dst) const {
	dst.append(word);
}
