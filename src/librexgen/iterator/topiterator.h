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


#ifndef SRC_LIBREXGEN_ITERATOR_TOPITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_TOPITERATOR_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/string/simplestring.h>

namespace rexgen {
  class TopIterator : public Iterator {
  public:
    explicit TopIterator(std::shared_ptr<Regex>& re) : Iterator() {
      needWord = false;
      child = re->iterator(state);
      assert(child != nullptr);

      // register regex alternatives
      updateReferences();

      // update references
      updateReferences();

      // update attributes (e.g. case folding )
      updateAttributes();
    }

    bool next() override {
      if (needWord) {
        bool res = state.getStreamIterator().lock()->forceNext();
        if (res) {
          needWord = false;
        }
        return res;
      }
      bool res = child->next();
      if (res) { return res; }

      if (! state.hasStreamIterator()) { return false; }
      res = state.getStreamIterator().lock()->forceNext();
      if (res) { return res; }
      needWord = true;
      return false;
    }

    void value(SimpleString *dst) const override { child->value(dst); }

    void updateReferences(IteratorState&/* ignore */) override {
      updateReferences();
    }

    void updateAttributes(IteratorState& /* ignore */ ) override {
      updateAttributes();
    }

    std::shared_ptr<SerializableState> getCurrentState() const override {
      return child->getCurrentState();
    }

    void setCurrentState(const std::shared_ptr<SerializableState>& s) override {
      child->setCurrentState(s);
    }

  private:

    void updateReferences() {
      if (child != nullptr) {
        child->updateReferences(state);
      }
    }

    void updateAttributes() {
      if (child != nullptr) {
        child->updateAttributes(state);
      }
    }

    std::shared_ptr<Iterator> child;
    IteratorState state;
    bool needWord;
  };
}
#endif  // SRC_LIBREXGEN_ITERATOR_TOPITERATOR_H_
