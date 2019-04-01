//
// Created by Jan Starke on 2019-04-01.
//

#ifndef PROJECT_REXGENGENERATOR_H
#define PROJECT_REXGENGENERATOR_H

#include <catch2/catch.hpp>
#include <librexgen/librexgen.h>
#include <string>

namespace rexgen {
  class RexgenGenerator : public Catch::Generators::IGenerator<std::string>{
  public:
    RexgenGenerator(const std::string& regex);

    std::string const& get() const override;
    bool next() override;

  private:
    std::string current_value;
    std::unique_ptr<Iterator> iterator;
  };
}

#endif //PROJECT_REXGENGENERATOR_H
