//
// Created by Jan Starke on 2019-04-01.
//

#include "RexgenGenerator.h"

namespace rexgen {

  RexgenGenerator::RexgenGenerator(const std::string& regex) {
    rexgen::RexgenOptions options;
    options.ignore_case = false;
    options.infile = NULL;
    iterator = regex_iterator(regex.c_str(), options);
  }
  std::string const& RexgenGenerator::get() const {
    return current_value;
  }
  bool RexgenGenerator::next() {
    if (iterator->next()) {
      current_value.clear();
      iterator->value(current_value);
      return true;
    } else {
      return false;
    }
  }
}