/*
    Copyright (c) 2012, Jan Starke <jan.starke@outofbed.org>
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
        * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
        * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
        * Neither the name of the <organization> nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
