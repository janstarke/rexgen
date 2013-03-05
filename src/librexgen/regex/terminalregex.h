#ifndef __TerminalRegex_h__
#define __TerminalRegex_h__

#include <librexgen/regex/regex.h>
#include <librexgen/iterator/terminalregexiterator.h>

class TerminalRegex : public Regex {
public:
  inline TerminalRegex(): value(_T("")) {}
  
  ~TerminalRegex() { delete value; }

  inline TerminalRegex(char_type c): value(new char_type[2]) {value[0]=c; value[1]='\0';}
  void prependSingleCharacter(const char_type* v);
  void setValue(const char_type* v);
  
  inline const char_type* getValue() const { return value; }
  
  inline const char_type* getXmlTag() const { return _C("terminal"); }
  
  RegexType getRegexType() const { return Terminal; }
  
  int appendContent(char_type* dst, ssize_t size, int level) const;
  
  Iterator* iterator(IteratorState* state) const;
  
  Iterator* singleIterator(IteratorState* /* state */) const
    { return new TerminalRegexIterator(getId(), value); }
private:
  char_type* value;
};

#endif