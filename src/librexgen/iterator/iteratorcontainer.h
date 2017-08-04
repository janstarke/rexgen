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


#ifndef SRC_LIBREXGEN_ITERATOR_ITERATORCONTAINER_H_
#define SRC_LIBREXGEN_ITERATOR_ITERATORCONTAINER_H_

#include <librexgen/iterator/iterator.h>
#include <vector>

#ifdef __cplusplus
class IteratorState;

class IteratorContainer : public Iterator {
 public:
  typedef std::vector<Iterator*> children_list_type;

  explicit IteratorContainer(int _id) : Iterator(_id) {}
  virtual ~IteratorContainer() {
    for (auto i : iterators) {
      if (!i->isSingleton()) {
        delete i;
      }
    }
  }

  virtual void updateAttributes(IteratorState* iterState) {
    for (Iterator* child : iterators) {
      child->updateAttributes(iterState);
    }
  }

  virtual void updateReferences(IteratorState* iterState) {
    for (Iterator* child : iterators) {
      child->updateReferences(iterState);
    }
  }

  virtual void addChild(Iterator* i) {
    iterators.push_back(i);
  }

 protected:
  void setPosition(children_list_type::iterator i) { iter = i; }
  void incrementPosition() { ++iter; }
  void resetPosition() { iter = iterators.begin(); }
  children_list_type::iterator getPosition() const { return iter; }

  children_list_type iterators;

 private:
  children_list_type::iterator iter;
};

#endif /* __cplusplus */

#endif /* SRC_LIBREXGEN_ITERATOR_ITERATORCONTAINER_H_ */
