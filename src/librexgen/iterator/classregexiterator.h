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
      std::for_each(begin, end, [this](const wchar_t& ch) {characters.append_widechar(ch);});
      std::string::size_type index = 0;
      for (size_t n = 0; n < characters.length(); ++n) {

        /*
         * TODO(jasa):
         * the call to character_length is very slow and should be removed
         */
        lengths.push_back(characters.character_length(n));

        indices.push_back(index);
        index += characters.character_length(n);
      }
      characters_count = static_cast<size_t>(characters.length());
      state = usable;
    }

    virtual ~ClassRegexIterator() {}

    virtual void updateReferences(IteratorState& /* iterState */) {}

    virtual void updateAttributes(IteratorState& /* iterState */) {}

    inline void value(SimpleString *dst) const {
      /**
        * FIXME(jasa):
        * this condition may be expensive and should be unnecessary
        */
      if (current >= 0) {
        const std::string::size_type &length = lengths[current];
        const std::string::size_type &index = indices[current];

        for (std::string::size_type n = 0; n < length; ++n) {
          dst->push_back(characters[index + n]);
        }
      }
    }

    bool next() {
      ++current;

      if (current >= static_cast<int>(characters_count)) {
        current = 0;
        return false;
      }
      return true;
    }

    size_t size() const { return characters_count; }

    inline bool hasNext() const {
      return (current < (static_cast<int>(characters_count) - 1));
    }

    inline bool canUseValue() const {
      return (current < static_cast<int>(characters_count));
    }

    std::shared_ptr<SerializableState> getCurrentState() const {
      auto s = Iterator::getCurrentState();
      s->addValue(canary);
      s->addValue(current);
      return s;
    }

    void setCurrentState(const std::shared_ptr<SerializableState>& s) {
      Iterator::setCurrentState(s);
      auto c = s->getValue(0);
      assert(c == canary);
      current = s->getValue(1);
    }

  private:
    /* use a signed int to by able to use index -1 */
    signed int current;

    /*
     * we must use this because multibyte characters
     * cannot be counted effectively
     */
    int characters_count;
    SimpleString characters;
    vector<std::string::size_type> indices;
    vector<std::string::size_type> lengths;

    static constexpr SerializableState::stateword_t canary = 0x73659035;
  };
}
#endif  // SRC_LIBREXGEN_ITERATOR_CLASSREGEXITERATOR_H_
