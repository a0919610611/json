[![JSON for Modern C++](https://raw.githubusercontent.com/nlohmann/json/master/doc/json.gif)](https://github.com/nlohmann/json/releases)
[![Build Status](https://travis-ci.org/a0919610611/json.svg?branch=develop)](https://travis-ci.org/a0919610611/json)
[![codecov](https://codecov.io/gh/a0919610611/json/branch/develop/graph/badge.svg)](https://codecov.io/gh/a0919610611/json)

## Links
[Hackmd/Report](https://hackmd.io/s/H12MTt0y7)

[Travis-ci](https://travis-ci.org/a0919610611/json)

[Codecov](https://codecov.io/gh/a0919610611/json)

[lcov Report](https://twleo.com/json/include/json.hpp.gcov.html)

[Slide](https://docs.google.com/presentation/d/1gcGfzOqwoCQ0D9C8agdzT0OjKqlOE4lVQbTsVep5QMk/edit?usp=sharing)

## Team Member
- 0416031 傅裕夫
- 0416223 許賀傑

## Develop Guide

### git hooks
```
cp hooks/* .git/hooks
```

### Compile and Run all test
- Make sure you have gcc-7 and newest lcov installed
- In the repo directory simply run `make test_run`

## How to compile a generic program
```
# Include "json.hpp" in your source code
# Use g++/clang++ at your own will
g++ main.cpp -std=c++11 -o main
```
