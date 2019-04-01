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
#include <librexgen/osdepend.h>
#include <librexgen/state/serializablestate.h>
#include <librexgen/state/invaliditeratoridexception.h>
#include <memory>
#include <string>

#ifdef __cplusplus
namespace rexgen {
  class IteratorState;

  class Iterator {
  public:

    explicit Iterator() :
            state(resetted),
            id(reinterpret_cast<uintptr_t>(this)) {
    }

    virtual ~Iterator() {}

    virtual bool hasNext() const { return false; }

    virtual bool next() = 0;

    //virtual void value(SimpleString * /* dst */) const {}
    virtual void value(std::string & /* dst */) const {}

    uintptr_t getId() const { return id; }

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

    virtual void updateReferences(IteratorState & /* iterState */) = 0;

    virtual void updateAttributes(IteratorState & /* iterState */) = 0;

    virtual std::shared_ptr<SerializableState> getCurrentState() const {
      return std::make_shared<SerializableState>(getId(), getState());
    }

    virtual void setCurrentState(const std::shared_ptr<SerializableState> &s) {
      setState(s->getStateEnum());
    }

  protected:
    enum state_t {
      resetted,
      usable,
      not_usable
    } state;

    static inline void append_widechar(std::string &dst, const wchar_t &widechar);

    static inline size_t character_length(std::string &, size_t idx);

    static inline wchar_t widechar_at(const std::string &str, size_t index);

  private:
    const uintptr_t id;
  };

  class NullIterator : public Iterator {
    bool next() override { throw std::runtime_error("not implemented"); }

    void updateReferences(IteratorState & /* iterState */) override { throw std::runtime_error("not implemented"); }

    void updateAttributes(IteratorState & /* iterState */) override { throw std::runtime_error("not implemented"); }
  };

  void Iterator::append_widechar(std::string &dst, const wchar_t &widechar) {
    char buffer[MB_LEN_MAX];
    int ch_size = std::wctomb(&buffer[0], widechar);

    if (ch_size == -1) {
      ch_size = 1;
      buffer[0] = '?';
    }

    dst.append(&buffer[0], ch_size);
  }

  size_t Iterator::character_length(std::string &dst, size_t idx) {
    int ch_size;
    int pos = 0;
    for (size_t i = 0; i < idx; ++i) {
      ch_size = mblen(&(dst.at(pos)), MB_CUR_MAX);
      assert(ch_size > 0 && ch_size <= 8);
      pos += ch_size;
    }
    ch_size = mblen(&(dst.at(pos)), MB_CUR_MAX);
    return static_cast<size_t>(ch_size);
  }

  wchar_t Iterator::widechar_at(const std::string &str, size_t index) {
    wchar_t widechar = 0;
    const int ch_size = std::mbtowc(&widechar, &(str.at(index)), MB_LEN_MAX);
    if (ch_size == -1) {
      const char questionmark = '?';
      std::mbtowc(&widechar, &questionmark, sizeof(questionmark));
    }
    return widechar;
  }
}

#endif /* __cplusplus */

#endif /* SRC_LIBREXGEN_ITERATOR_ITERATOR_H_ */
