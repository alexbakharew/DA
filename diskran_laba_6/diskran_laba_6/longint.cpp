#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "longint.h"
const int base = 100000;
const int radix = 5;
//const int MAX_VALUE = 99999;
TLongInt::TLongInt() {}

TLongInt::TLongInt(const std::string &number)
{
    for (int i = number.size(); i > 0; i -= 5)
    {
        if (i < 5)
            Data.push_back (atoi (number.substr (0, i).c_str()));
        else
            Data.push_back (atoi (number.substr (i-5, 5).c_str()));
    }
    while(Data.back() == 0 && Data.size() > 1)
        Data.pop_back();
}

void TLongInt::print()
{
    printf("%d", Data.empty() ? 0 : Data.back());// We avoid zeros in the begining
    for (int i = Data.size() - 2; i >= 0; --i)
        printf ("%05li", Data[i]);
    printf("\n");
    return;
}
void TLongInt::operator +=(const TLongInt& other)
{
    int k = 0;
    for (size_t i = 0; i < std::max(Data.size(),other.Data.size()); ++i)
    {
        if(i == Data.size())
            Data.push_back(0);

        Data[i] += (other.Data.size() <= i ? 0 : other.Data[i]) + k;
        k = Data[i] / base;
        Data[i] %= base;
    }
    if( k != 0)
        Data.push_back(k);
    return;
}
bool TLongInt::operator -=(const TLongInt& other)
{
    if(Data.size() < other.Data.size())
        return false;
    int maxSize = std::max(Data.size(), other.Data.size());
    int k = 0;
    for(int i = 0; i < maxSize; ++i)
    {
        Data[i] += k;
        k = 0;
        int otherVal = (other.Data.size() <= i ? 0 : other.Data[i]);
        if(Data[i] < otherVal)
        {
            k = -1;
            Data[i] += base;
        }
        Data[i] -= otherVal;
    }
    if(k != 0)
        return false;
    else
        return true;
}
bool TLongInt::operator ==(const TLongInt& other)
{
    if(Data.size() != other.Data.size()) return false;
    else
    {
        for(size_t i = 0; i < Data.size(); ++i)
        {
            if(Data[i] != other.Data[i]) return false;
            else
                continue;
        }
        return true;
    }
}
bool TLongInt::operator >(const TLongInt& other)
{
    if(Data.size() > other.Data.size()) return true;
    else
    {
        for(size_t i = 0; i < Data.size(); ++i)
        {
            if(Data[i] <= other.Data[i]) return false;
            else
                continue;
        }
        return true;
    }
}
bool TLongInt::operator <(const TLongInt& other)
{
    if(Data.size() < other.Data.size()) return true;
    else
    {
        for(size_t i = 0; i < Data.size(); ++i)
        {
            if(Data[i] >= other.Data[i]) return false;
            else
                continue;
        }
        return true;
    }
}
TLongInt TLongInt::operator *(const TLongInt& other)
{
    TLongInt result("0");
    if(other.Data.back() == 0 || this->Data.back() == 0)
        return result;
    result.Data.resize(other.Data.size() + Data.size(), 0);
    for(int i = 0; i < other.Data.size(); ++i)
    {
        int k = 0;// remainder
        for(int j = 0; j < this->Data.size(); ++j)
        {
            int t = (other.Data[i] * this->Data[j]) + result.Data[i + j] + k;
            k = t / base;
            result.Data[i + j] = t % base;
        }
        result.Data[this->Data.size() + i] = k;
    }
    if(result.Data.back() == 0)
        result.Data.pop_back();
    return result;
}
TLongInt TLongInt::pow(int n)
{

}













