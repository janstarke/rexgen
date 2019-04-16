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
#include <utils.h>
#include <FuzzerGenerator.h>
#include <librexgen/librexgen.h>
#include <librexgen/rexgen_options.h>
#include <librexgen/iterator/topiterator.h>
#include <set>
#include <pcrecpp.h>

TEST_CASE("testing with libFuzzer", "libFuzzerTest") {

  rexgen::RexgenOptions options;

  SECTION("Nice UX") {
    auto FUZZY_VALUE = GENERATE(take(10000, rexgen::catch2::fuzzer()));
    auto regex = parse_regex(FUZZY_VALUE.c_str(), options);
    if (regex != nullptr) {
      auto iter = std::make_unique<rexgen::TopIterator>(regex);
      REQUIRE(iter != nullptr);
    }
  }
}