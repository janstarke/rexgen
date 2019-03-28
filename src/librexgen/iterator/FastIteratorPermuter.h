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

#ifndef PROJECT_FASTITERATORPERMUTER_H
#define PROJECT_FASTITERATORPERMUTER_H

#include <librexgen/iterator/iterator.h>
#include <librexgen/string/unicode.h>
#include <librexgen/iterator/iteratorcontainer.h>
#include <type_traits>

namespace rexgen {

  template<class ITERATOR>
  class FastIteratorPermuter : public Iterator {
    static_assert(std::is_base_of<Iterator, ITERATOR>::value, "must be an iterator");
    static_assert(std::is_default_constructible<ITERATOR>::value, "Iterator for FastIteratorPermuter must be default constructable");

  public:
    FastIteratorPermuter(unsigned int count) : iterators(count) {
      /* keep the first element as is */
      for(size_t n=1; n<count; ++n) {iterators[n].next();}
    }

    void value(SimpleString *dst) const override {
      for (const auto& i : iterators) { i.value(dst);}
    }

    bool next() override {
      for (auto&& i : iterators) { if (i.next()) { return true; } }
      return false;
    }


    void updateAttributes(IteratorState& iterState) override {
      for (auto&& child : iterators) { child.updateAttributes(iterState); }
    }

    void updateReferences(IteratorState& iterState) override {
      for (auto&& child : iterators) { child.updateReferences(iterState); }
    }

  private:
    std::vector<ITERATOR> iterators;
  };
}


#endif //PROJECT_FASTITERATORPERMUTER_H
