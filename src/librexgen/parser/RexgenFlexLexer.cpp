//
// Created by Jan Starke on 2019-03-12.
//

#include <librexgen/parser/RexgenFlexLexer.h>
#include <librexgen/parser/rexgenparsingdriver.h>

namespace rexgen {

  static const char MULTIBYTE_MARKER = 0xfe;
  static constexpr char ESCAPED_MULTIBYTE_MARKER[] = "\\xFE";

  RexgenFlexLexer::RexgenFlexLexer(const std::string &input) {
    std::string::const_iterator input_ptr = input.begin();
    int size;
    wchar_t wc = 0;
    mbstate_t mbs;
    std::memset(&mbs, 0, sizeof(mbs));
    while (input_ptr != input.cend()) {
      size = mbrtowc(&wc, input_ptr.base(), MB_CUR_MAX, &mbs);
      if (size == 0) {
        break;
      }
      assert (size > 0);
      int single_byte = wctob(wc);
      if (single_byte != EOF) {
        /* mask 0xfe */
        if (single_byte == MULTIBYTE_MARKER) {
          content.append(ESCAPED_MULTIBYTE_MARKER);
        } else {
          content.push_back(static_cast<char>(single_byte));
        }
      } else {
        content.push_back(static_cast<char>(MULTIBYTE_MARKER));
        wcontent.push_back(wc);
      }

      input_ptr += size;
    }
    content_ptr = content.cbegin();
    wcontent_ptr = wcontent.begin();
  }

  int RexgenFlexLexer::LexerInput( char* buf, int max_size ) {
    int size = 0;
    while (max_size-- > 0 && content_ptr != content.cend()) {
      *buf++ = *content_ptr++;
      ++size;
    }
    return size;
  }

  RexgenParser::symbol_type RexgenFlexLexer::beginGroupWithOptions(RexgenParsingDriver& driver) const {
    bool enable_mode = true;
    int handle_case = CASE_IGNORE;
    for (int idx=2; idx < yyleng-1; ++idx) {
      switch(yytext[idx]) {
        case 'i':
          handle_case =
                  enable_mode
                  ?	CASE_ITERATE
                  : CASE_IGNORE ;
          break;
        case '-':
          enable_mode = false;
          break;
        default:
          throw SyntaxError("Invalid modifier for special group");
      }
    }
    return RexgenParser::make_T_BEGIN_GROUP(std::make_shared<t_group_options>(handle_case, driver.nextGroupId()));
  }

  RexgenParser::symbol_type RexgenFlexLexer::beginGroup(RexgenParsingDriver& driver) const {
    return RexgenParser::make_T_BEGIN_GROUP(std::make_shared<t_group_options>(driver.nextGroupId()));
  }

  char RexgenFlexLexer::hex2bin(const char c) {
    if (c>='0' && c<='9') return c-'0';
    if (c>='a' && c<='f') return (10+c-'a');
    if (c>='A' && c<='F') return (10+c-'A');
    return (char)0xff;
  }

  char RexgenFlexLexer::parseAnsiChar(const char* text) {
    return (hex2bin(text[2])<<4) | (hex2bin(text[3]));
  }

  uint32_t RexgenFlexLexer::parseUnicodeChar(const char* text) {
    return (hex2bin(text[2])<<12)
           | (hex2bin(text[3])<<8)
           | (hex2bin(text[4])<<4)
           | (hex2bin(text[5]));
  }

  void RexgenFlexLexer::UTF8_validate_second_byte(const unsigned char c) {
    if (c < 0x80 || c >= 0xC0) {
      throw SyntaxError("invalid UTF8  byte sequence");
    }
  }

  uint32_t RexgenFlexLexer::parseUTF8(const unsigned char* text) {
    if (text[0] < 0x80) { return text[0]; }
    if (text[0] < 0xC0) { throw SyntaxError("invalid UTF8 byte sequence"); }
    if (text[0] <= 0xDF) {
      UTF8_validate_second_byte(text[1]);
      return    ( (0x1F & text[0])<<6)
                | (  0x3F & text[1]);
    }

    if (text[0] <= 0xEF) {
      UTF8_validate_second_byte(text[1]);
      UTF8_validate_second_byte(text[2]);
      return    ( (0x0F & text[0])<<12)
                | ( (0x3F & text[1])<<6)
                | (  0x3F & text[2]);
    }

    if (text[0] <= 0xF7) {
      UTF8_validate_second_byte(text[1]);
      UTF8_validate_second_byte(text[2]);
      UTF8_validate_second_byte(text[3]);
      return    ( (0x0F & text[0])<<18)
                | ( (0x3F & text[1])<<12)
                | ( (0x3F & text[2])<<6)
                | (  0x3F & text[3]);
    }
    throw SyntaxError("unknown UTF8 byte sequence");
  }
}