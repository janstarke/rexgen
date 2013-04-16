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


#include <librexgen/iterator/groupreferenceiterator.h>
#include <librexgen/debug.h>

bool GroupReferenceIterator::hasNext() const {
  ENTER_METHOD;
  RETURN(state == resetted);
}

bool GroupReferenceIterator::next() {
  ENTER_METHOD;
  bool res = (state == resetted);
  state = usable;
  RETURN(res);
}

void GroupReferenceIterator::value(SimpleString& dst) const {
  ENTER_METHOD;
  groupRef->value(dst);
  LEAVE_METHOD;
}

void GroupReferenceIterator::reset() {
  Iterator::reset();
  state = resetted;
}
