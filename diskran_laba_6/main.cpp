#include <iostream>
#include <cstdlib>
#include <string>
#include <climits>
#include "longint.h"
int main()
{
    /*std::string num1;
    std::string num2;
    char operation;
    while(std::cin>>num1>>num2>>operation)
    {
        TLongInt n1(num1);
        TLongInt n2(num2);
        switch(operation)
        {
            case '+':
            {

                //std::cout<<n1<<" + "<<n2<<" = ";
                n1 += n2;
                n1.print();
                continue;
            }
            case '-':
            {
                if(n1 -= n2)
                    n1.print();
                else
                    printf("Error\n");
                continue;
            }
            case '*':
            {
                TLongInt res = n1 * n2;
                res.print();
                continue;

            }
            case '/':
            {
               std::cout<<operation;
               continue;
            }
            case '^':
            {
                std::cout<<operation;
                continue;
            }
            case '=':
            {
                if(n1 == n2) printf("true\n");
                else
                    printf("false\n");
                continue;
            }
            case '>':
            {
                if(n1 > n2) printf("true\n");
                else
                    printf("false\n");
                continue;
            }
            case '<':
            {
                if(n1 < n2) printf("true\n");
                else
                    printf("false\n");
                continue;
            }
        }
    }*/
    TLongInt n1, n2;
//    std::cin >> n1;
//    std::cin >> n2;
    /*if(n1 == n2)
        std::cout << "n1 = n2\n"; // TODO
    else if(n1 > n2)
        std::cout << "n1 > n2\n"; // TODO
    if(n1 < n2)
        std::cout << "n1 < n2\n"; // TODO
    */
    while(1)
    {
        std::cin >> n1;
        std::cin >> n2;
        TLongInt res = n1 * n2;
        std::cout << res << std::endl;
    }

    return 0;
}

