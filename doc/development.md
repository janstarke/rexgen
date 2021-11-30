# Developer Documentation

## Building rexgen

### Using the build script

```bash
# build with debug symbols
./build.sh -d

# alternative: build with debug symbols and profiling instrumentation, run tests
./build.sh -t
```

### Building `rexgen` manually

```bash
mkdir build
cd build
cmake ../src -DCMAKE_BUILD_TYPE=DEBUG
```

## Generating API documentation

```bash
# generates API doxumentation in XML format in doxygen/xml
doxygen doxygen/doxygen.conf

# install moxygen
git clone https://github.com/sourcey/moxygen.git
cd moxygen
npm install
cd ..

# convert XML format to markdown
moxygen/bin/moxygen.js --output doc/api.md doxygen/xml/
```