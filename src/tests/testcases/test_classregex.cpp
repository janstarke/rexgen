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

#include "gtest/gtest.h"
#include <utils.h>
#include <librexgen/librexgen.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/classregex.h>
#include <librexgen/iterator/classregexiterator.h>
#include <set>
#include <pcrecpp.h>

TEST(ClassIteratorTest, TestEmptyIterator) {
  Iterator* iter = new ClassRegexIterator(1, (const wchar_t*) L"", 0);
  ASSERT_FALSE(iter->next());
  ASSERT_FALSE(iter->next());
  delete iter;
}

TEST(ClassIteratorTest, TestIteratorWithOneElement) {
  Iterator* iter = new ClassRegexIterator(1, (const wchar_t*) L"a", 1);
  SimpleString str;
  iter->value(&str);
  ASSERT_STREQ(str.c_str(), "");
  str.clear();
  ASSERT_TRUE(iter->next());
  iter->value(&str);
  ASSERT_STREQ(str.c_str(), "a");
  str.clear();

  ASSERT_FALSE(iter->next());
  iter->value(&str);
  ASSERT_STREQ(str.c_str(), "a");
  str.clear();

  ASSERT_FALSE(iter->next());
  iter->value(&str);
  ASSERT_STREQ(str.c_str(), "a");
  delete iter;
}

TEST(ClassIteratorTest, TestSingle1) {validateRegex("[]",                    0);}
TEST(ClassIteratorTest, TestSingle2) {validateRegex("[a]",                   1);}
TEST(ClassIteratorTest, TestDigits1) {validateRegex("\\d",                  10);}
TEST(ClassIteratorTest, TestDigits2) {validateRegex("[\\d]",                10);}
TEST(ClassIteratorTest, TestDigits3) {validateRegex("[\\d\\d]",             10);}
TEST(ClassIteratorTest, TestSpaces1) {validateRegex("\\s",                   2);}
TEST(ClassIteratorTest, TestSpaces2) {validateRegex("[\\s]",                 2);}
TEST(ClassIteratorTest, TestSpaces3) {validateRegex("[\\s\\s]",              2);}
TEST(ClassIteratorTest, TestClass01) {validateRegex("([a-b])test([0-1g-h])", 8);}
TEST(ClassIteratorTest, TestClass02) {validateRegex("[-0-9a-zA-Z]",         63);}
TEST(ClassIteratorTest, TestClass03) {validateRegex("\\w",                  63);}
TEST(ClassIteratorTest, TestClass04) {validateRegex("[a-z]",                26);}
TEST(ClassIteratorTest, TestClass05) {validateRegex("[A-Z]",                26);}
TEST(ClassIteratorTest, TestClass06) {validateRegex("[a-f]",                 6);}
TEST(ClassIteratorTest, TestClass07) {validateRegex("[A-F]",                 6);}
TEST(ClassIteratorTest, TestClass08) {validateRegex("[c-a]",                 0);}
TEST(ClassIteratorTest, TestClass09) {validateRegex("[3-6]",                 4);}
TEST(ClassIteratorTest, TestClass10) {validateRegex("[0-9]",                10);}
TEST(ClassIteratorTest, TestClass11) {validateRegex("[\\d0-9]",             10);}
TEST(ClassIteratorTest, TestClass12) {validateRegex("[\\w0-9]",             63);}
TEST(ClassIteratorTest, TestClass13) {validateRegex("[\\wa-z]",             63);}
TEST(ClassIteratorTest, TestClass14) {validateRegex("[\\wA-Z]",             63);}
TEST(ClassIteratorTest, TestClass15) {validateRegex("[\\w\\d]",             63);}
TEST(ClassIteratorTest, TestClass16) {validateRegex("[\\d\\w]",             63);}
