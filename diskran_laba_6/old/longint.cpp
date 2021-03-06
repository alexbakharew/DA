#include <iostream>
#include <cstdlib>
#include "longint.h"

TLongInt::TLongInt(){}

TLongInt::TLongInt(const std::string& num)
{
    int tmp;

    for(int i = num.size(); i >= 0; i -= CAPACITY)
    {
        if(i < CAPACITY)
            tmp = std::stoi(num.substr(0, i));
        else
            tmp = std::stoi(num.substr(i - CAPACITY, CAPACITY));

        Data.push_back(tmp);
    }

    while(Data.back() == 0 && Data.size() > 1) //geting rid of leading zeros
        Data.pop_back();

}

TLongInt::TLongInt(const uint64_t& num)
{
    std::string charNum = std::to_string(num);
    *this = TLongInt(charNum);
}

std::istream& operator >> (std::istream& is, TLongInt& num)
{
    if(!num.Data.empty())// case when we use one variable twice or more
    {
        num.Data.clear();
        num.Data.shrink_to_fit();
    }

    std::string s; //string for raw input
    is >> s;

    int tmp; //temp variable for pushing into the vector

    for(int i = s.size(); i > 0; i -= CAPACITY)
    {
        if(i < 6)
            tmp = std::stoi(s.substr(0, i));
        else
            tmp = std::stoi(s.substr(i - CAPACITY, CAPACITY));

        num.Data.push_back(tmp);
    }

    while(num.Data.back() == 0 && num.Data.size() > 1)//geting rid of leading zeros
        num.Data.pop_back();

    return is;
}

std::ostream& operator << (std::ostream& os, const TLongInt& num)
{

    printf("%li", (num.Data.empty() ? 0 : num.Data.back()));

    for(int i = num.Data.size() - 2; i >= 0; --i)
        printf("%06li", num.Data[i]);

    printf("\n");
    return os;
}

void TLongInt::operator = (const uint64_t& num)
{
    *this = TLongInt(num);
}
void TLongInt::operator = (const TLongInt& num)
{//this = num
    Data.clear();
    Data.resize(num.Data.size());

    for(int i = 0; i < Data.size(); ++i)
        Data[i] = num.Data[i];

    return;
}

bool TLongInt::operator < (const TLongInt& num)
{
    if(Data.size() < num.Data.size())
        return true;

    else if(Data.size() > num.Data.size())
        return false;

    else
    {
        bool equalOnly = true;
        for(int i = Data.size() - 1; i >= 0; --i)
        {
            if(Data[i] < num.Data[i])
            {
                equalOnly = false;
                continue;
            }

            else if(Data[i] == num.Data[i])
                continue;

            else return false;
        }

        if(equalOnly)//num1 == num2
            return false;
        else
            return true;

        return true;
    }
}

bool TLongInt::operator > (const TLongInt& num)
{
    if(Data.size() > num.Data.size())
        return true;

    else if(Data.size() < num.Data.size())
        return false;

    else
    {
        bool equalOnly = true;
        for(int i = Data.size() - 1; i >= 0; --i)
        {
            if(Data[i] > num.Data[i])
            {
                equalOnly = false;
                continue;
            }

            else if(Data[i] == num.Data[i])
                continue;

            else return false;
        }

        if(equalOnly)//num1 == num2
            return false;
        else
            return true;

        return true;
    }
}

bool TLongInt::operator == (const TLongInt& num)
{
    if(Data.size() != num.Data.size())
        return false;
    else
    {
        for(int i = Data.size() - 1; i >= 0; --i)
        {
            if(Data[i] == num.Data[i])
                continue;

            else return false;
        }
        return true;
    }
}

bool TLongInt::operator == (const uint64_t& num)
{
    TLongInt tmp(num);
    return *this == tmp;
}
bool TLongInt::operator >= (const TLongInt& num)
{
    if(*this > num || *this == num)
        return true;
    else
        return false;
}
bool TLongInt::operator >= (const uint64_t& num)
{
    return *this >= TLongInt(num);
}
bool TLongInt::operator != (const TLongInt& num)
{
    if(*this == num)
        return false;
    else
        return true;
}

bool TLongInt::operator != (const uint64_t& num)
{
    TLongInt tmp(num);
    return *this != tmp;
}
void TLongInt::operator += (const TLongInt& num)
{
    if(num.Data.size() == 1 && num.Data[0] == 0)// addition by zero
        return;

    int remainder = 0;

    for(int i = 0; i < std::max(Data.size(), num.Data.size()); ++i)
    {
        if(i == Data.size())
            Data.push_back(0);

        Data[i] += (i >= num.Data.size() ? 0 : num.Data[i]) + remainder;
        remainder = Data[i] / BASE;
        Data[i] %= BASE;
    }

    if(remainder != 0)
        Data.push_back(remainder);

    return;
}

void TLongInt::operator -= (const TLongInt& num)
{//this -= num
    if(num.Data.size() == 1 && num.Data[0] == 0)// subtraction by zero
        return;

    int remainder = 0;

    for(int i = 0; i < std::max(Data.size(), num.Data.size()); ++i)
    {
        Data[i] += remainder;
        remainder = 0;
        if(Data[i] < (i >= num.Data.size() ? 0 : num.Data[i]))
        {
            Data[i] += BASE;
            remainder = -1;
        }
         Data[i] -= (i >= num.Data.size() ? 0 : num.Data[i]);
    }

    while(Data.back() == 0 && Data.size() > 1)
        Data.pop_back();

    return;
}

void TLongInt::operator *= (const TLongInt& num)
{   //num *= num1 ~ num = num * num1
    if(Data.size() == 1)
    {
        if(Data[0] == 0) //multiplication by zero
            return;//nothing to change
        else if(Data[0] == 1) // multiplication by one
        {
            Data.resize(num.Data.size());
            for(int i = 0; i < Data.size(); ++i)//simply copy second number into first
                Data[i] = num.Data[i];
            return;
        }
    }

    if(num.Data.size() == 1)
    {
        if(num.Data[0] == 0) //multiplication by zero
        {
            Data.resize(num.Data.size());
            Data[0] = 0;
            return;
        }
        else if(num.Data[0] == 1) //multiplication by one
            return;//nothing to change
    }

    std::vector<uint64_t> res(Data.size() + num.Data.size());
    for(int i = 0; i < Data.size(); ++i)
    {
        int remainder = 0;
        for(int j = 0; j < num.Data.size(); ++ j)
        {
            res[i + j] += remainder + (uint64_t(Data[i]) * uint64_t(num.Data[j]));
            remainder = res[i + j] / BASE;
            res[i + j] %= BASE;
        }

        if(remainder != 0)
            res[num.Data.size() + i] = remainder;
    }

    while(res.back() == 0 && res.size() > 1)// avoid zeros
        res.pop_back();

    Data.resize(res.size());//final changes for this number
    for(int i = 0; i < res.size(); ++i)
        Data[i] = res[i];

    return;
}

void TLongInt::operator *= (const long long& n)
{
    TLongInt charNum(n);
    *this *= charNum;
    return;
}

TLongInt TLongInt::operator * (const TLongInt& num)
{// res = num1 * num2
    if(Data.size() == 1)
    {
        if(Data[0] == 0) //multiplication by zero
            return TLongInt("0");
        else if(Data[0] == 1) // multiplication by one
            return num;
    }

    if(num.Data.size() == 1)
    {
        if(num.Data[0] == 0) //multiplication by zero
            return TLongInt("0");
        else if(num.Data[0] == 1) //multiplication by one
            return *this;
    }

    std::vector<uint64_t> res(Data.size() + num.Data.size());
    for(int i = 0; i < Data.size(); ++i)
    {
        int remainder = 0;
        for(int j = 0; j < num.Data.size(); ++ j)
        {
            res[i + j] += remainder + (uint64_t(Data[i]) * uint64_t(num.Data[j]));
            remainder = res[i + j] / BASE;
            res[i + j] %= BASE;
        }

        if(remainder != 0)
            res[num.Data.size() + i] = remainder;
    }

    while(res.back() == 0 && res.size() > 1)
        res.pop_back();

    TLongInt res_num;
    for(auto i : res)
        res_num.Data.push_back(i);

    return res_num;
}

TLongInt TLongInt::Power(long pow)
{
    TLongInt result("1");
    if(pow == 0)
        return result;
    while (pow > 0)
    {
        if (pow % 2 == 1)
            result *= (*this);
        (*this) *= (*this);
        pow /= 2;
    }
    return result;
}

size_t TLongInt::Size()
{
    return Data.size();
}

void TLongInt::addZero(int n)
{
    for(int i = 0; i < n; ++i)
        Data.insert(Data.begin(), 0);
}
void TLongInt::delZero()
{
    Data.erase(Data.begin());
    //I suppose that first elem is 0 when I use this method
}
void TLongInt::operator /= (TLongInt& div)
{// this /= div
    //it's known that this >= that divider
    if(*this == 1)
    {
        *this = 0;
        return;
    }
    if(div == 1)
        return;

    if(*this == div)
    {
        *this = 1;
        return;
    }
    std::string res;
    for(int i = this->Size() - div.Size(); i >= 0; --i)
    {
        TLongInt divider = div;
        divider.addZero(i);
        if(*this < divider)
            divider.delZero();
        int count = 0;
        while(*this >= divider)
        {
            *this -= divider;
            ++count;
        }
        if(*this != 0)
            --count;
        res += std::to_string(count);
    }


    *this = TLongInt(res);
    return;
}


void TLongInt::operator %= (TLongInt& div)
{// this /= div
    //it's known that this >= that divider
    if(*this == 1)
    {
        *this = 0;
        return;
    }
    if(div == 1)
        return;

    if(*this == div)
    {
        *this = 1;
        return;
    }
    std::string res;
    int k = this->Size() - div.Size();
    for(int i = k; i >= 0; --i)
    {
        TLongInt divider = div;
        divider.addZero(i);
        if(*this < divider)
            divider.delZero();
        int count = 1;
        while(*this >= divider)
        {
            *this -= divider;
            ++count;
        }
        res += std::to_string(count);
    }
//    *this = TLongInt(res);
    return;
}








