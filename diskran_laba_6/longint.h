#ifndef LONGINT
#define LONGINT
#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
//int countCapacity();
//
const int BASE = 1000000;
//
const int CAPACITY = 6;

class TLongInt
{
public:
    TLongInt();
    TLongInt(const std::string& n);
    TLongInt(const uint64_t& n);
    friend std::istream& operator >> (std::istream& is, TLongInt& n);
    friend std::ostream& operator << (std::ostream& os, const TLongInt& n);
    bool operator < (const TLongInt& num);
    bool operator > (const TLongInt& num);
    bool operator >= (const TLongInt& num);
    bool operator >= (const uint64_t& num);
    bool operator == (const TLongInt& num);
    bool operator == (const uint64_t& num);
    bool operator != (const TLongInt& num);
    bool operator != (const uint64_t& num);
    void operator = (const TLongInt& num);
    void operator = (const uint64_t& num);
    void operator += (const TLongInt& num);
    void operator -= (const TLongInt& num);
    void operator *= (const TLongInt& num);
    void operator *= (const long long& num);
    void operator /= (TLongInt& num);
    void operator %= (TLongInt& num);
    TLongInt operator * (const TLongInt& divider);
    TLongInt Power(long pow);
    size_t Size();
    void addZero(int n);//function for quick multiplication on current BASE * n
    void delZero();//function for quick division on current BASE

private:
    std::vector<int> Data;

};

#endif // LONGINT

