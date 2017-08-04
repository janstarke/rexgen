/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

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

#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/regex/groupreference.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/iterator/groupreferenceiterator.h>
#include <librexgen/string/simplestring.h>

Iterator* GroupReference::singleIterator(IteratorState* /* state */) const {
  assert(groupRef != NULL);
  return new GroupReferenceIterator(getId(), groupRef->getGroupId());
}

