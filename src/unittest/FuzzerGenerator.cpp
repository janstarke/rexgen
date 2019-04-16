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

#include <FuzzerGenerator.h>
#include <catch2/catch.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

static std::thread catch2_worker;

static void run_session(std::shared_ptr<rexgen::catch2::FuzzerQueue> queue, int catch2_argc, char** catch2_argv) {
  static Catch::Session session;
  /* keep shared ptr of queue */
  auto q = queue;
  session.run(catch2_argc, catch2_argv);
  q = nullptr;
}

extern "C" int LLVMFuzzerInitialize(int *argc, char ***argv) {
  std::thread t(run_session, rexgen::catch2::FuzzerQueue::sharedInstance(), *argc, *argv);
  catch2_worker = std::move(t);
  return 0;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (auto ptr = rexgen::catch2::FuzzerQueue::weakInstance().lock()) {
    ptr->set(data, size);
  } else {
    raise(SIGTERM);
  }
  return 0;
}

namespace Catch {
  std::ostream& cout() {
    return std::cerr;
  }
  std::ostream& clog() {
    return std::cerr;
  }
  std::ostream& cerr() {
    return std::cerr;
  }
}


namespace rexgen {
  namespace catch2 {

    std::weak_ptr<FuzzerQueue> FuzzerQueue::instance;
    std::shared_ptr<FuzzerQueue> FuzzerQueue::sharedInstance() {
      if (auto ptr = instance.lock()) {
        return ptr;
      }
      auto ptr = std::make_shared<FuzzerQueue>();
      instance = ptr;
      return ptr;
    }

    static void run_session(int catch2_argc, char** catch2_argv) {
      static Catch::Session session;
      session.run(catch2_argc, catch2_argv);
      raise(SIGTERM);
    }

    void FuzzerQueue::set(const uint8_t* data, size_t size) {
      auto predicate = [this]{return finish_worker || !has_input;};
      if (finish_worker) { return; }

      {
        std::unique_lock<std::mutex> lock(input_mutex);
        writer.wait(lock, predicate);
        if (finish_worker) { return; }

        input_buffer.clear();
        input_buffer.reserve(size);
        input_buffer.insert(input_buffer.begin(), data, data + size);
        has_input = true;

      }
      proxy.notify_all();
    }

    std::string const & FuzzerQueue::get() const {
      std::lock_guard<std::mutex> lock(value_mutex);
      return current_value;
    }

    bool FuzzerQueue::next() {
      auto predicate = [this] {return (finish_worker || has_input);};
      std::string tmp;
      {
        std::unique_lock<std::mutex> lock(input_mutex);
        proxy.wait(lock, predicate);

        if (finish_worker) { return false; }

        tmp = std::move(input_buffer);
        has_input = false;
      }
      /* enable writers and writers */
      writer.notify_all();

      {
        std::lock_guard<std::mutex> lock(value_mutex);
        current_value = std::move(tmp);
      }
      return true;
    }
  }
}