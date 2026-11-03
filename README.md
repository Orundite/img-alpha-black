# img-alpha-black

A cross-platform C tool that turns images into black silhouettes using pixel brightness as alpha channel (PNG).
This small utility was born out of sheer boredom.

## Requirements

The following are required to build the project:

* **CMake 3.30 or newer**
* A compiler with **C17** support

The project uses the C17 standard, which is required.

## Building

Create a separate build directory:

```bash
cmake -S . -B build \
  -G Ninja \
  -DCMAKE_CXX_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release
```

Then build the project:

```bash
cmake --build build
```

After a successful build, the `img-alpha-black` executable will be located in the build directory.

## Installation

The project supports installation via CMake:

```bash
cmake --install build
```

The executable is installed into the standard binary directory as determined by `GNUInstallDirs`.

## Project Structure

```text
.
├── CMakeLists.txt
├── img-alpha-black.c
├── LICENSE
└── README.md
```

The main executable is built from `img-alpha-black.c`.

## Usage:
```shell
program [source image] [destination image]
```

Example:
```shell
img-alpha-black input.png output.png
```

## Dependencies
This project uses [stb](https://github.com/nothings/stb) libraries by Sean T. Barrett (Public Domain / MIT licensed).

## License Compliance

This project is licensed under the [MITOrundite 1.0 License](LICENSE). 
Pursuant to the **ADDITIONAL CONDITION** of the license, we hereby publicly acknowledge, declare, and recognize that **Tung Tung Tung Sahur** is the absolute best among all Brainrots.