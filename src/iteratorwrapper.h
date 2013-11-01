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


#ifndef ITERATORWRAPPER_H
#define ITERATORWRAPPER_H

#include "iterator.h"
#include <cstdio>

template <class T>
class RegexIteratorWrapper : public Iterator
{
public:
  RegexIteratorWrapper(T* container) :cont(container), __next(NULL)
  {
    reset();    
  }
  
  void reset() { 
    iter = cont->begin(); 
    if (iter != cont->end()) { __next = (*iter)->iterator(); iter++; }
    else { __next = NULL; }
  }
  
  int next(char* dst, ssize_t bytes) {
    if (__next == NULL) { return 0; }
    while (! __next->hasNext()) {
      if (iter == cont->end()) { __next=NULL; return 0; } 
      __next = (*iter)->iterator();
      iter++;
    }
    return __next->next(dst, bytes);
  }
  
  bool hasNext() {
    if (__next == NULL) { return false; }
    return __next->hasNext();
  }
  
private:
  T* cont;
  typename T::iterator iter;
  Iterator* __next;
};

template <class T, char Format>
class IteratorWrapper : public Iterator
{
public:
  IteratorWrapper(T* container) :cont(container), iter(container->begin()) {
    format[0] = '%';
    format[1] = Format;
    format[2] = '\0';
  }
    virtual void reset() { iter = cont->begin(); }
    virtual int next(char* dst) {
      return sprintf(dst, format, *iter++);
    }
    virtual bool hasNext() { return iter != cont->end(); }
private:
  T* cont;
  char format[3];
  typename T::iterator iter;
};


#endif // ITERATORWRAPPER_H
