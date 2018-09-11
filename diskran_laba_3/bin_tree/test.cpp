#include <iostream>
int* func()
{
    int* tmp = new int;
    *tmp = 20;
    return tmp;
}
int main()
{
    int* aPtr = func();
    std::cout<<*aPtr<<std::endl;

}