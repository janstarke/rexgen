# rexgen

A tool to create words based on regular expressions.

# Requirements

To build rexgen, you'll need the following tools and libs:

| Tool | needed for |
|------|------------|
| flex | Generator for lexical analysis of regular expressions |
| bison | Generator of parser for regular expressions |
| cmake | Creation of Makefiles |

# Building rexgen

Clone the git repository to include the required FindICU:
```
git clone https://github.com/teeshop/rexgen.git
```

Build and install:
```bash
cd rexgen
./install.sh
# you can use the switches -p to enable python support and -l to enable lua support
```

# Architecture

If you are interested in contributing, please have a look at the (Architecture Documentation)[doc/architecture.md]

## Problems

If you have problems building rexgen, you can change to the `build` directory and run `cmake .. && make` manually.
Currently supported options for rexgen's CMakefile are:

* `-DCMAKE_BUILD_TYPE=Debug` creates a debug build
* `-DUSE_PYTHON=On` tells cmake to include the python interface
* `-DUSE_LUA=On` tells cmake to include the lua python interface

# Support

If you want to contribute ideas, bug reports or improvements to this project, feel free to contact me via github. 

If you are not interested in active participation of this project, but you want to support it anyway, you can 
[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=jan.starke&url=https://github.com/teeshop/rexgen&title=rexgen&language=en&tags=github&category=software)

# License

Copyright (C) 2012-2017  Jan Starke <jan.starke@outofbed.org>

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
