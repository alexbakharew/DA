#include <exception>
#include <new>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "equation.h"

int main(int argc, char *argv[]) {

    std::size_t n, m;
    std::cin >> n >> m;
    Equation **mData = new Equation*[n];

    for (std::size_t i = 0; i < n; i++) {
        mData[i] = new Equation(m, i);
        std::cin >> mData[i];
    }

    std::vector<std::size_t> answer = FindMinCost(mData, n, m);
    if (!answer.empty()) {
        for (std::size_t i = 0; i < answer.size() - 1; i++) {
            std::cout << std::to_string(answer[i]) + " ";
        }

        std::cout << std::to_string(answer[answer.size() - 1])
                                                    << std::endl;
    } else {
        std::cout << std::to_string(-1) << std::endl;
    }
    for (int i = 0; i < n; i++) {
        delete mData[i];
    }
    delete [] mData;
}