![GitHub Workflow Status](https://img.shields.io/github/workflow/status/janstarke/rexgen/CMake)

# rexgen

A tool to create words based on regular expressions.

# Requirements

To build rexgen, you'll need the following tools and libs:

| Tool | needed for |
|------|------------|
| flex | Generator for lexical analysis of regular expressions |
| bison | Generator of parser for regular expressions |
| cmake | Creation of Makefiles |
| clang | Compiling the code |

On Ubuntu, you can install these via e.g.

```
sudo apt install flex libfl-dev libbison-dev cmake clang bison
```

# Building rexgen

Clone the git repository to include the required FindICU:
```
git clone https://github.com/janstarke/rexgen.git
```

Build and install:
```bash
cd rexgen
./install.sh
# you can use the switches -p to enable python support and -l to enable lua support
```

# Architecture

If you are interested in contributing, please have a look at
 - [Architecture Documentation](doc/architecture.md)
 - [API documentation](doc/api.md)
 - [Developer documentation](doc/development.md)

## Problems

If you have problems building rexgen, you can change to the `build` directory and run `cmake .. && make` manually.
Currently supported options for rexgen's CMakefile are:

* `-DCMAKE_BUILD_TYPE=Debug` creates a debug build
* `-DUSE_PYTHON=On` tells cmake to include the python interface
* `-DUSE_LUA=On` tells cmake to include the lua python interface

## Using the C++ API

```C++
rexgen::RexgenOptions options;
auto regex = parse_regex("Test[0-9]", options);
assert(regex != nullptr);

auto iter = std::make_shared<rexgen::TopIterator>(regex);

SimpleString str;
while (iter->next()) {
    str.clear();
    iter->value(&str);
    std::cout << str.c_str() << std::endl;
}
```

# License

Copyright (C) 2012-2021  Jan Starke <jan.starke@outofbed.org>

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
