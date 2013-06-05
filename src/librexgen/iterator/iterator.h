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


#ifndef ITERATOR_H
#define ITERATOR_H

#include <assert.h>
#include <librexgen/unicode.h>
#include <librexgen/simplestring.h>

class IteratorState;

class Iterator
{
public:

  Iterator(int _id):
    state(resetted), 
    id(_id) {}
  virtual ~Iterator() {}
  
  virtual bool hasNext() const { return false; }
  virtual bool next() = 0;
  virtual void value(SimpleString& /* dst */ ) const { }
  
  virtual bool canUseValue() const { return (state == usable); }
  
  int getId() const { return id; }
  
  virtual void updateReferences(IteratorState* /* iterState */) = 0;
  virtual bool isSingleton() const { return false; }
protected:
  
  enum {
    resetted,
    usable,
    not_usable
  } state;
  
private:
  const int id;
};

#endif // ITERATOR_H
