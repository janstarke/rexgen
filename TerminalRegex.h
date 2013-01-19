#ifndef __TerminalRegex_h__
#define __TerminalRegex_h__

#include "Regex.h"
#include "terminalregexiterator.h"

class TerminalRegex : public Regex {
public:
  inline TerminalRegex(): value(_T("")) {}
  
  ~TerminalRegex() { delete value; }
  
  inline TerminalRegex(char_type* str): value(NULL) {
    ssize_t size = utf_strlen(str);
    value = new char_type[size];
    utf_strncpy(value, str, size);
  }
  inline TerminalRegex(char_type c): value(new char_type[2]) {value[0]=c; value[1]='\0';}
  inline void prependCharacter(const char_type* v) {
    char_type* tmp = value;
    ssize_t size = 1 + utf_strlen(tmp) + 1;
    value = new char_type[size];
    value[0] = parseFirstCharacter(v);
    utf_strncpy(&value[1], tmp, size);
    delete tmp;
  }
  inline void setValue(const char_type* v) {
    delete value;
    ssize_t size = utf_strlen(v)+1;
    value = new char_type[size];
    utf_strncpy(value, v, size);
  }
  inline const char_type* getValue() const { return value; }
  
  virtual inline const char_type* getXmlTag() const { return _T("terminal"); }
  
  virtual int appendContent(char_type* dst, ssize_t size, int level) const { 
    int l, length = 0;
    const char* format;
    l = appendSpace(dst, size, level);
    length += l;
    if ((size -= l) < 0) goto finish;
    dst += l;
    
#if defined(UTF8)
    format = "%U\n";
#elif defined(UTF16)
    format = "%lU\n";
#else
    format = "%llU\n";
#endif
    length += utf_snprintf(dst, size, format, value);
finish:
    return length;
  }
  
  Iterator* iterator() const
  { return new IteratorPermuter(getId(), this, getMinOccurs(), getMaxOccurs()); }
  
  Iterator* singleIterator() const
    { return new TerminalRegexIterator(getId(), value); }
private:
  char_type* value;
};

#endif