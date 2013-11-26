/*
    rexgen - a tool to create words based on regular expressions    
    Copyright (C) 2012-2013  Jan Starke <jan.starke@outofbed.org>

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


#ifndef ITERATOR_H
#define ITERATOR_H

#include <assert.h>
#include <librexgen/unicode.h>
#include <librexgen/simplestring.h>
#include <librexgen/osdepend.h>

#ifdef __cplusplus
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

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C" {
#endif

typedef void* c_iterator_ptr;

EXPORT
c_iterator_ptr c_regex_iterator(
				const char* regex_str,
				int ignore_case,
				charset encoding,
				int randomize,
				FILE* infile);

EXPORT
int c_iterator_next(c_iterator_ptr iter);
EXPORT
void c_iterator_value(c_iterator_ptr next, c_simplestring_ptr dst);
EXPORT
void c_iterator_delete(c_iterator_ptr i);

#ifdef __cplusplus
}
#endif

#endif /* ITERATOR_H */
