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

#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/regex/groupreference.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/iterator/groupreferenceiterator.h>
#include <librexgen/simplestring.h>

Iterator* GroupReference::singleIterator(IteratorState* /* state */) const {
  assert(groupRef != NULL);
  return new GroupReferenceIterator(getId(), groupRef->getGroupId());
}

void GroupReference::appendContent(
    SimpleString& dst, int level) const {
  appendSpace(dst, level);
  dst.append(groupRef->getId());
}
