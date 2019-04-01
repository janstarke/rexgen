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


#ifndef SRC_LIBREXGEN_ITERATOR_CLASSREGEXITERATOR_H_
#define SRC_LIBREXGEN_ITERATOR_CLASSREGEXITERATOR_H_

#include <librexgen/iterator/iterator.h>
#include <librexgen/iterator/iteratorstate.h>
#include <librexgen/string/unicode.h>
#include <librexgen/string/simplestring.h>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>

namespace rexgen {
  class ClassRegexIterator : public Iterator {
  public:

    template <class Iter>
    ClassRegexIterator(Iter begin, Iter end)
            : Iterator(), current(-1), characters() {
      std::for_each(begin, end, [this](const wchar_t& ch) {append_widechar(characters, ch);});
      std::string::size_type index = 0;
      for (size_t n = 0; n < characters.length(); ++n) {

        /*
         * TODO(jasa):
         * the call to character_length is very slow and should be removed
         */
        lengths.push_back(character_length(characters, n));

        indices.push_back(index);
        index += character_length(characters, n);
      }
      characters_count = static_cast<size_t>(characters.length());
      state = usable;
    }

    virtual ~ClassRegexIterator() {}

    void updateReferences(IteratorState& /* iterState */) override {}

    void updateAttributes(IteratorState& /* iterState */) override {}

    inline void value(std::string& dst) const override {
      /**
        * FIXME(jasa):
        * this condition may be expensive and should be unnecessary
        */
      if (current >= 0) {
        const std::string::size_type &length = lengths[current];
        const std::string::size_type &index = indices[current];

        for (std::string::size_type n = 0; n < length; ++n) {
          dst.push_back(characters[index + n]);
        }
      }
    }

    bool next() override {
      ++current;

      if (current >= static_cast<int>(characters_count)) {
        current = 0;
        return false;
      }
      return true;
    }

    size_t size() const { return characters_count; }

    std::shared_ptr<SerializableState> getCurrentState() const override {
      auto s = Iterator::getCurrentState();
      s->addValue(current);
      return s;
    }

    void setCurrentState(const std::shared_ptr<SerializableState>& s) override {
      Iterator::setCurrentState(s);
      current = s->getValue(0);
    }

  private:
    /* use a signed int to by able to use index -1 */
    signed int current;

    /*
     * we must use this because multibyte characters
     * cannot be counted effectively
     */
    int characters_count;
    std::string characters;
    vector<std::string::size_type> indices;
    vector<std::string::size_type> lengths;
  };
}
#endif  // SRC_LIBREXGEN_ITERATOR_CLASSREGEXITERATOR_H_
