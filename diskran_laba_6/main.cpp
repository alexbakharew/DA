#include <iostream>
#include <cstdlib>
#include <string>
#include "longint.h"
int main()
{
    std::string num1;
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
    }
    return 0;
}

