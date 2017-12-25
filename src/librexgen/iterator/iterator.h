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

  virtual bool next() = 0;
  virtual void value(SimpleString* /* dst */) const = 0;

  int getId() const { return id; }

  typedef enum {
    resetted,
    usable
  } state_t;
  virtual int getState() const { return state; }
  virtual void setState(state_t _state) {
    state = _state;
  }
  virtual void updateReferences(IteratorState* /* iterState */) = 0;
  virtual void updateAttributes(IteratorState* /* iterState */) = 0;
  virtual bool isSingleton() const { return false; }

  virtual SerializableState* getCurrentState() const {
    return new SerializableState(getId(), getState());
  }

  virtual void setCurrentState(const SerializableState* s) {
    assert (getId() == s->getIteratorId());
    setState(static_cast<state_t>(s->getStateEnum()));
  }

private:
  state_t state;

  const int id;
};

#endif /* __cplusplus */

#endif /* SRC_LIBREXGEN_ITERATOR_ITERATOR_H_ */
