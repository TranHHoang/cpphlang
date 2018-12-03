[![Build Status](https://travis-ci.org/TranHHoang/cpphlang.svg?branch=master)](https://travis-ci.org/TranHHoang/cpphlang)

# H Programming Language
Aim to replace `C++` and other languages in programming contest.
It provides the best performance of native code, concise, less error-prone and high readability
with good `standard library`


## Usage
Follow the instructions to get a copy of the project on local machine
### Prerequisites

You will need:

- CMake 3.2
- C++ compiler with C++11 support
- LLVM

### Building the project

#### Git Clone

```bash
$ git clone https://github.com/TranHHoang/cpphlang.git
```

#### Project Structure
- `bin` — Empty until `make install`
- `build` — CMake build files
- `doc` — Documentation (Placeholder)
- `include` — Project header files
- `lib` — Third-party library (Placeholder)
- `src` — Project source files
- `test` — Google Unit Testing

#### Building Manually

```bash
$ cmake

# build/release when needed
$ cd build/debug

$ make && make install
```

#### Building in CLion
> Recommend, since this project is created with CLion

Select menu option **Run ➜ Build**, and then **Run ➜ Install**.

#### Contributing

### License

&copy; 2018 Tran Huu Hoang

Open sourced under MIT license, the terms of which can be read here — [MIT License](http://opensource.org/licenses/MIT).