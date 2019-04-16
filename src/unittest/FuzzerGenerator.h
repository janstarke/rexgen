/*
    rexgen - a tool to create words based on regular expressions
    Copyright (C) 2012-2019  Jan Starke <jan.starke@outofbed.org>

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

#ifndef PROJECT_FUZZERGENERATOR_H
#define PROJECT_FUZZERGENERATOR_H

#include <librexgen/librexgen.h>
#include <string>
#include <thread>
#include <mutex>
#include <iostream>
#include <condition_variable>
#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_NOSTDOUT
#include <catch2/catch.hpp>

namespace rexgen {
  namespace catch2 {

    class FuzzerQueue {
    public:
      static std::weak_ptr<FuzzerQueue> weakInstance() { return instance; }
      static std::shared_ptr<FuzzerQueue> sharedInstance();

      void               set(const uint8_t *data, size_t size);
      std::string const &get() const;
      bool               next();
    private:
      std::atomic_bool finish_worker = false;
      static std::weak_ptr<FuzzerQueue> instance;
      mutable std::mutex input_mutex;
      mutable std::mutex value_mutex;
      mutable std::condition_variable proxy;
      mutable std::condition_variable writer;
      mutable std::string input_buffer;
      mutable std::string current_value;
      mutable std::atomic_bool has_input = false;
    };

    class FuzzerGenerator : public Catch::Generators::IGenerator<std::string> {
    public:
      FuzzerGenerator(std::shared_ptr<FuzzerQueue> queue): queue(queue) {}

      inline std::string const &get() const override { return queue->get(); }
      inline bool               next()      override { return queue->next(); }
    private:
      std::shared_ptr<FuzzerQueue> queue;
    };

    inline
    Catch::Generators::GeneratorWrapper<std::string>
    fuzzer() {
      return Catch::Generators::GeneratorWrapper<std::string>(
              std::make_unique<FuzzerGenerator>(FuzzerQueue::sharedInstance())
              );
    }
  }
}

#endif //PROJECT_FUZZERGENERATOR_H
