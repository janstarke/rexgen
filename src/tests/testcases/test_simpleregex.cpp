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
#include "../utils.h"
#include <librexgen/librexgen.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/regex/classregex.h>
#include <librexgen/iterator/classregexiterator.h>
#include <set>
#include <pcrecpp.h>

TEST(SimpleRegexTest, TestSimple1) {validateRegex("test[0-9]",  10);}
TEST(SimpleRegexTest, TestSimple2) {validateRegex("test[\\d]",  10);}
TEST(SimpleRegexTest, TestSimple3) {validateRegex("test[a\\d]", 11);}
TEST(SimpleRegexTest, TestSimple4) {validateRegex("test[\\da]", 11);}
TEST(SimpleRegexTest, TestSimple5) {validateRegex("test\\da",   10);}
TEST(SimpleRegexTest, TestSimple6) {validateRegex("a\\dtest",   10);}