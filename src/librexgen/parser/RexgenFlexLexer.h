//
// Created by Jan Starke on 2019-03-12.
//

#ifndef PROJECT_REXGENFLEXLEXER_H
#define PROJECT_REXGENFLEXLEXER_H

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "parser.hpp"
#include <istream>
#include <memory>

namespace rexgen {
  class RexgenFlexLexer : public yyFlexLexer {
  public:
    RexgenFlexLexer(const std::string& input);

    RexgenParser::symbol_type rexgen_lex(RexgenParsingDriver& driver);
    int LexerInput( char* buf, int max_size ) override;

    /*
     * PARSER FUNCTIONS
     */
    rexgen::RexgenParser::symbol_type beginGroupWithOptions(RexgenParsingDriver& driver) const;
    rexgen::RexgenParser::symbol_type beginGroup(RexgenParsingDriver& driver) const;

    /*
     * HELPER FUNCTIONS
     */
    static char hex2bin(const char c);
    static char parseAnsiChar(const char* text);
    static uint32_t parseUnicodeChar(const char* text);
    static void UTF8_validate_second_byte(const unsigned char c);
    static uint32_t parseUTF8(const unsigned char* text);
  private:
    std::string content;
    std::string::const_iterator content_ptr;
    std::wstring wcontent;
    std::wstring::const_iterator wcontent_ptr;
  };
}


#endif //PROJECT_REXGENFLEXLEXER_H
