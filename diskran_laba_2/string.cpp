#include <iostream>
#include <cstring>
#include <stdio.h>
#include "string.h"
const int DefaultCapacity = 4;
TString::TString(const char* str)
{
    Size = std::strlen(str);
    Buffer = new char[Size + 1];
    std::memcpy(Buffer, str, Size);
    Buffer[Size] = '\0';
}
TString::TString()
{
    Buffer = new char[DefaultCapacity];
    Size = 0;
    Capacity = DefaultCapacity;
    
    for(;;)
    {
        int ch = getchar();
        Buffer[Size] = ch;
        if(ch == '\0' || ch == '\n') break;
        ++Size;
        if(Size == Capacity)
        {
            char* tmp = new char[Size];
            std::memcpy(tmp, Buffer, Size);
            Buffer = new char[Capacity * 2];
            Capacity *= 2;
            std::memcpy(Buffer, tmp, Size);
            delete[] tmp;
        }
        
    }
}
void TString::Print()
{
    printf("%s\n", Buffer);
}
TString::~TString()
{
    delete[] Buffer;
}
char* TString::GetStr()
{
    return Buffer;
}
