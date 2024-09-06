# oopd-a1
Source Files for the OOPD Assignment 1

## Instructions for running
- Running `make` or `make all` will compile both the versions of the program, i.e `ltcg_debug` meant for debugging using -g flag and `ltcg_optimized` compiled using O2 flag.
- Running `make clean` will clean up the executables.
- The file `main.cpp` contains the source of the program and `ltcg_debug` and `ltcg_optimized` are the executables.
- The input file used for the program is `price-inflation.csv` which must be in the same directory as the executables.
## References Used
- std::setprecision: [CPP Reference - setprecision](https://en.cppreference.com/w/cpp/io/manip/setprecision)
- std::fixed: [CPP Reference - fixed](https://en.cppreference.com/w/cpp/io/manip/fixed)
- std::runtime_error: [CPP Reference - runtime_error](https://en.cppreference.com/w/cpp/error/runtime_error)
- std::string: [CPP Reference - string](https://en.cppreference.com/w/cpp/string/basic_string)
- std::ifstream: [CPP Reference - ifstream](https://en.cppreference.com/w/cpp/io/basic_ifstream)