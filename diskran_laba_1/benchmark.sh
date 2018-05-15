#! /bin/bash
make
echo "Time for radix sort"
time ./*1 < tests/01.t > /dev/null
g++ -std=c++11 benchmark.cpp

echo "Time for std::sort()"
time ./a.out < tests/01.t > /dev/null