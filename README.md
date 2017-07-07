# vsl-bindgen

[![Build status](https://ci.appveyor.com/api/projects/status/5ygjuiqjq4locml5/branch/master?svg=true)](https://ci.appveyor.com/project/vihanb/vsl-bindgen/branch/master)

A converter to create VSL bindings for a C/C++ header file.

## Installation

### Windows
Download a pre-built version from the [artifacts](https://ci.appveyor.com/project/vihanb/vsl-bindgen) and place it in your `PATH`.

### Linux

You must have `CMake`, `Clang`/`LLVM`, and a C++ toolchain. Then run:

```bash
$ mkdir build
$ cd build
$ cmake ..
$ cd ..
$ make
$ sudo make install
```

## Usage

Use bindgen through `vsl bindgen` as the C++ app itself uses a binary format for
I/O and options.
