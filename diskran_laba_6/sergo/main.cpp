#include <iostream>
#include <algorithm>
#include "TBigInt.h"


int main() {
    std::string lineNum1, lineNum2;
    char sign;
    while (std::cin >> lineNum1 >> lineNum2 >> sign) {
        TBigInt a(lineNum1);
        TBigInt b(lineNum2);
        TBigInt result;
        switch (sign) {
            case '+':
                result = a + b;
                std::cout << result << std::endl;
                break;
            case '-':
                if (a < b) {
                    std::cout<< "Error\n";
                } else {
                    result = a - b;
                    std::cout << result << std::endl;
                }
                break;
            case '/':
                if (b == 0) {
                    std::cout << "Error\n";
                } else {
                    result = a / b;
                    std::cout << result << std::endl;
                }
                break;
            case '*':
                result = a * b;
                std::cout << result << std::endl;
                break;
            case '^':
                if ((a == 0) && (b == 0)) {
                        std::cout << "Error\n";
                } else {
                    result = a ^ b;
                    std::cout << result << std::endl;
                }
                break;
            case '>':
                std::cout << (a > b ? "true" : "false") << std::endl;
                break;
            case '<':
                std::cout << (a < b ? "true" : "false") << std::endl;
                break;
            case '=':
                std::cout << (a == b ? "true" : "false") << std::endl;
                break;
            default:
                std::cout << "Uncorrect requests" << std::endl;
                break;
        }
    }
    return 0;
}
