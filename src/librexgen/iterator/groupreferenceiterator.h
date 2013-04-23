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


#ifndef GROUPREFERENCEITERATOR_H
#define GROUPREFERENCEITERATOR_H

#include "iterator.h"
#include <librexgen/regex/regex.h>
#include <vector>
#include <librexgen/unicode.h>


class GroupReferenceIterator : public Iterator
{

public:
    GroupReferenceIterator(int _id, const Iterator* re)
      : Iterator(_id), groupRef(re) {};
  
    virtual bool hasNext() const;
    virtual bool next();
    virtual void value(SimpleString& dst) const;
    //virtual void reset();
    
private:
  const Iterator* groupRef;
};

#endif // GROUPREFERENCEITERATOR_H
