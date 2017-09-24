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

TEST(ClassIteratorTest, TestDigits) {validateRegex("\\d",                  10);}
TEST(ClassIteratorTest, TestClass1) {validateRegex("([a-b])test([0-1g-h])", 8);}
TEST(ClassIteratorTest, TestClass2) {validateRegex("[-0-9a-zA-Z]",         63);}
TEST(ClassIteratorTest, TestClass3) {validateRegex("\\w",                  63);}
TEST(ClassIteratorTest, TestClass4) {validateRegex("[a-f]",                 6);}
TEST(ClassIteratorTest, TestClass5) {validateRegex("[A-F]",                 6);}
TEST(ClassIteratorTest, TestClass6) {validateRegex("[c-a]",                 0);}
TEST(ClassIteratorTest, TestClass7) {validateRegex("[3-6]",                 4);}
