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

TEST_CASE("CaseIteratorTest01", "TestCases01") {validateRegex("(?i:abc)",         8);}
TEST_CASE("CaseIteratorTest02", "TestCases02") {validateRegex("(?i:a(?i:bc))",2*2*8);}
TEST_CASE("CaseIteratorTest03", "TestCases03") {validateRegex("(?i:[abc])-[pP]", 12);}
TEST_CASE("CaseIteratorTest04", "TestCases04") {validateFailure("(?i:abcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcdefghijabcde)");}
TEST_CASE("CaseIteratorTest05", "TestCases05") {validateRegex(  "(?i:a1234567890123456789012345678901234567890123456789012345678901234)", 2);}
TEST_CASE("CaseIteratorTest06", "TestCases06") {validateRegex("(?i:[123]abc){3}", 3*3*3*8*8*8);}