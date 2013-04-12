#ifndef __TerminalRegex_h__
#define __TerminalRegex_h__

#include <librexgen/regex/regex.h>
#include <librexgen/iterator/terminalregexiterator.h>
#include <librexgen/iterator/iteratorpermuter.h>
#include <librexgen/unicode.h>
#include <librexgen/unicode/uchar.h>
#include <vector>

using std::vector;

class TerminalRegex : public Regex {
public:  
  TerminalRegex(uint32_t ch, charset encoding) {
    uchar_t uch;
    codepoint_to_uchar(&uch, ch, encoding);
    value.push_back(uch);
  }

  void prepend(const TerminalRegex* tre);
  /*
  void setValue(const char* v);
  */
  
  inline const char_type* getValue() const { return nullptr; }
  
  inline const char_type* getXmlTag() const { return _C("terminal"); }
  
  RegexType getRegexType() const { return Terminal; }
  
  int appendContent(char_type* dst, size_t size, int level) const;
  
  Iterator* iterator(IteratorState* state) const;
  
  Iterator* singleIterator(IteratorState* /* state */) const
    { return new TerminalRegexIterator(getId(), &value[0], value.size()); }
private:
  vector<uchar_t> value;
};
  
#endif
