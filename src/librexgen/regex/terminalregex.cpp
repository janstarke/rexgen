#include "terminalregex.h"
#include "../iterator/iteratorpermuter.h"
#include "../unicode.h"

void TerminalRegex::prependSingleCharacter(const char_type* v)
{
    char_type* tmp = value;
    ssize_t size = 	1 		/* the new character */
		  + 	utf_strlen(tmp)	/* the old value */
		  +	1;		/* the trailing null byte */
    value = new char_type[size];
    value[0] = parseFirstCharacter(v);
    utf_strncpy(&value[1], tmp, size-1);
    delete tmp;
}

void TerminalRegex::setValue(const char_type* v)
{
    delete value;
    ssize_t size = utf_strlen(v)+1;
    value = new char_type[size];
    utf_strncpy(value, v, size);
}

int TerminalRegex::appendContent(char_type* dst, ssize_t size, int level) const
{ 
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

Iterator* TerminalRegex::iterator(IteratorState* state) const
{
  if (getMinOccurs() == 1 && getMaxOccurs() == 1) {
    return new TerminalRegexIterator(getId(), value);
  } else {
    return new IteratorPermuter<TerminalRegex>(getId(), this, state, getMinOccurs(), getMaxOccurs());
  }
}