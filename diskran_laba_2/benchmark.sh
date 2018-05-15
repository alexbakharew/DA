#! /bin/bash
make
echo "Time for AVL-tree"
time ./*2 < tests/01.t > tmp
g++ -std=c++11 benchmark.cpp
echo "Time for MAP from STL"
time ./a.out < tests/01.t > tmp