#include "lint.h"
#include <string>
int main()
{
    apa::lint a("76234");
    apa::lint b("76234");
    std::cout<<a+b<<std::endl;
    return 0;
}