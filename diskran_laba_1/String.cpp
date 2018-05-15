#include <iostream>
#include <cstdio>
#include <cstdlib>
TString::TString(){}
void TString::print()
{
    printf("%s", Buffer);
}
char TString::operator [](size_t n)
{
    return Buffer[n];
}
TString::~TString()
{
    //std::cout<<"String was deleted"<<std::endl;
}
