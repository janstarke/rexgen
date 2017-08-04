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


#ifndef SRC_LIBREXGEN_ITERATOR_ITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_ITERATOR_H_

#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <librexgen/osdepend.h>
#include <librexgen/state/serializablestate.h>
#include <librexgen/state/invaliditeratoridexception.h>

#ifdef __cplusplus
class IteratorState;

class Iterator {
 public:
  explicit Iterator(int _id):
    state(resetted),
    id(_id) {}
  virtual ~Iterator() {}

  virtual bool hasNext() const { return false; }
  virtual bool next() = 0;
  virtual void value(SimpleString* /* dst */) const { }

  virtual bool canUseValue() const { return (state == usable); }

  int getId() const { return id; }
  virtual int getState() const { return state; }
  virtual void setState(int _state) {
    if (_state < static_cast<int>(resetted)) {
      state = not_usable;
    } else if (_state > static_cast<int>(not_usable)) {
      state = not_usable;
    } else {
      state = static_cast<state_t>(_state);
    }
  }
  virtual void updateReferences(IteratorState* /* iterState */) = 0;
  virtual void updateAttributes(IteratorState* /* iterState */) = 0;
  virtual bool isSingleton() const { return false; }

  virtual SerializableState* getCurrentState() const {
    return new SerializableState(getId(), getState());
  }

  virtual void setCurrentState(const SerializableState* s) {
    if (getId() != s->getIteratorId()) {
      throw InvalidIteratorIdException();
    }
    setState(s->getStateEnum());
  }

 protected:
  enum state_t {
    resetted,
    usable,
    not_usable
  } state;

 private:
  const int id;
};

#endif /* __cplusplus */

#endif /* SRC_LIBREXGEN_ITERATOR_ITERATOR_H_ */
