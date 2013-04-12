/*
 *    Copyright (c) 2013, Jan Starke <jan.starke@outofbed.org>
 *    All rights reserved.
 * 
 *    Redistribution and use in source and binary forms, with or without
 *    modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 * Neither the name of the <organization> nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 * 
 *    THIS SOFTWARE IS PROVIDED BY Jan Starke <jan.starke@outofbed.org> ''AS IS'' AND ANY
 *    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *    DISCLAIMED. IN NO EVENT SHALL Jan Starke <jan.starke@outofbed.org> BE LIABLE FOR ANY
 *    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef ANSI_STRING_H
#define ANSI_STRING_H

#include <iostream>
#include "uchar.h"

using std::ostream;

class ansi_string
{
public:
  ansi_string(size_t msize=256)
  :max_size(msize), current_size(0) {
    buffer = new char[msize];
  }
  virtual ~ansi_string() { delete[] buffer; }
  
  void push_back(char ch) {
    if (current_size < max_size) {
      buffer[current_size] = ch;
      current_size++;
    }
  }
  
  void push_back(u_char ch) {
    if (ch.variant == UTF8 && ch.length == 1) {
      push_back(ch.character.ansi.value);
    } else {
      push_back('?');
    }
  }
  
  size_t size() { return current_size; }
  void clear() { current_size = 0; }
  friend ostream& operator<<(ostream& stream, const ansi_string& str) const;
  
  virtual size_t size() = 0;
  virtual void clear() = 0;
  virtual char& operator[](size_t index) = 0;
  friend ostream& operator<<(ostream& stream, const char* str);
  
private:
  size_t max_size;
  size_t current_size;
  char* buffer;
};

ostream& operator<<(ostream& stream, const ansi_string& str) const {
  stream << str.buffer;
}

#endif // ANSI_STRING_H
