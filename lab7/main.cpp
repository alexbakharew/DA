#include <iostream>
#include <vector>
#include <stack>
#include "TMatrix.h"
using namespace std;
int main(int argc, char *argv[]) {
    std::size_t n, m;
    std::cin >> n >> m;
    TMatrix matrix(n, m);
    std::cin >> matrix;
//    std::cout << matrix;
//    std::cout << matrix.FindMaxSubMatrixTrivial(0) << std::endl;
    std::cout << matrix.FindMaxSubMatrixFast(0) << std::endl;
    return 0;
}
