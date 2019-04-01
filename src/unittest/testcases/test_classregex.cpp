/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2017 Jan Starke <jan.starke@outofbed.org>

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

#include <catch2/catch.hpp>
#include "../utils.h"
#include <librexgen/librexgen.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/classregex.h>
#include <librexgen/iterator/classregexiterator.h>
#include <set>
#include <pcrecpp.h>
#include <string>

using Catch::Matchers::Equals;

TEST_CASE("TestEmptyIterator", "TestEmptyIterator") {
  std::wstring wstr(L"");
  rexgen::Iterator* iter = new rexgen::ClassRegexIterator(wstr.cbegin(), wstr.cend());
  REQUIRE_FALSE(iter->next());
  REQUIRE_FALSE(iter->next());
  delete iter;
}

TEST_CASE("TestIteratorWithOneElement", "TestIteratorWithOneElement") {
  std::wstring wstr(L"a");
  rexgen::Iterator* iter = new rexgen::ClassRegexIterator(wstr.cbegin(), wstr.cend());
  std::string str;
  iter->value(str);
  REQUIRE_THAT(str, Equals(""));
  str.clear();
  REQUIRE(iter->next());
  iter->value(str);
  REQUIRE_THAT(str, Equals("a"));
  str.clear();

  REQUIRE_FALSE(iter->next());
  iter->value(str);
  REQUIRE_THAT(str, Equals("a"));
  str.clear();

  REQUIRE_FALSE(iter->next());
  iter->value(str);
  REQUIRE_THAT(str, Equals("a"));
  delete iter;
}

TEST_CASE("TestSingle1", "TestSingle1") {validateRegex("[]",                    0);}
TEST_CASE("TestSingle2", "TestSingle2") {validateRegex("[a]",                   1);}
TEST_CASE("TestDigits1", "TestDigits1") {validateRegex("\\d",                  10);}
TEST_CASE("TestDigits2", "TestDigits2") {validateRegex("[\\d]",                10);}
TEST_CASE("TestDigits3", "TestDigits3") {validateRegex("[\\d\\d]",             10);}
TEST_CASE("TestSpaces1", "TestSpaces1") {validateRegex("\\s",                   2);}
TEST_CASE("TestSpaces2", "TestSpaces2") {validateRegex("[\\s]",                 2);}
TEST_CASE("TestSpaces3", "TestSpaces3") {validateRegex("[\\s\\s]",              2);}
TEST_CASE("TestClass01", "TestClass01") {validateRegex("([a-b])test([0-1g-h])", 8);}
TEST_CASE("TestClass02", "TestClass02") {validateRegex("[-0-9a-zA-Z]",         63);}
TEST_CASE("TestClass03", "TestClass03") {validateRegex("\\w",                  63);}
TEST_CASE("TestClass04", "TestClass04") {validateRegex("[a-z]",                26);}
TEST_CASE("TestClass05", "TestClass05") {validateRegex("[A-Z]",                26);}
TEST_CASE("TestClass06", "TestClass06") {validateRegex("[a-f]",                 6);}
TEST_CASE("TestClass07", "TestClass07") {validateRegex("[A-F]",                 6);}
TEST_CASE("TestClass08", "TestClass08") {validateRegex("[c-a]",                 0);}
TEST_CASE("TestClass09", "TestClass09") {validateRegex("[3-6]",                 4);}
TEST_CASE("TestClass10", "TestClass10") {validateRegex("[0-9]",                10);}
TEST_CASE("TestClass15", "TestClass15") {validateRegex("[\\w\\d]",             63);}
TEST_CASE("TestClass16", "TestClass16") {validateRegex("[\\d\\w]",             63);}
TEST_CASE("TestClass17", "TestClass17") {validateRegex("[\\s0-9]",             12);}
TEST_CASE("TestClass18", "TestClass18") {validateRegex("[0-9\\s]",             12);}

TEST_CASE("TestDoubleCharacters01", "TestDoubleCharacters01") {validateRegex("[\\d0-9]",             10);}
TEST_CASE("TestDoubleCharacters02", "TestDoubleCharacters02") {validateRegex("[3\\d3]",              10);}
TEST_CASE("TestDoubleCharacters03", "TestDoubleCharacters03") {validateRegex("[\\w0-9]",             63);}
TEST_CASE("TestDoubleCharacters04", "TestDoubleCharacters04") {validateRegex("[3\\w3]",              63);}
TEST_CASE("TestDoubleCharacters05", "TestDoubleCharacters05") {validateRegex("[\\wa-z]",             63);}
TEST_CASE("TestDoubleCharacters06", "TestDoubleCharacters06") {validateRegex("[\\wcdec]",            63);}
TEST_CASE("TestDoubleCharacters07", "TestDoubleCharacters07") {validateRegex("[\\wA-Z]",             63);}
TEST_CASE("TestDoubleCharacters08", "TestDoubleCharacters08") {validateRegex("[\\wCDEC]",            63);}
TEST_CASE("TestDoubleCharacters09", "TestDoubleCharacters09") {validateRegex("[0-9\\d]",             10);}
TEST_CASE("TestDoubleCharacters10", "TestDoubleCharacters10") {validateRegex("[0-9\\w]",             63);}
TEST_CASE("TestDoubleCharacters11", "TestDoubleCharacters11") {validateRegex("[a-z\\w]",             63);}
TEST_CASE("TestDoubleCharacters12", "TestDoubleCharacters12") {validateRegex("[A-Z\\w]",             63);}
TEST_CASE("TestDoubleCharacters13", "TestDoubleCharacters13") {validateRegex("[a-fg\\wz]",           63);}
TEST_CASE("TestDoubleCharacters14", "TestDoubleCharacters14") {validateRegex("[a-f$\\wz]",           64);}
TEST_CASE("TestDoubleCharacters15", "TestDoubleCharacters15") {validateRegex("[a-f$\\w$]",           64);}
