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
    friend std::istream& operator >> (std::istream& is, TLongInt& n);
    friend std::ostream& operator << (std::ostream& os, const TLongInt& n);
    bool operator < (const TLongInt& num);
    bool operator > (const TLongInt& num);
    bool operator == (const TLongInt& num);
    void operator = (const TLongInt& num);
    void operator += (const TLongInt& num);
    void operator -= (const TLongInt& num);
    void operator *= (const TLongInt& num);
    TLongInt operator * (const TLongInt& num);
    TLongInt Power(long pow);


private:
    std::vector<int> Data;
};

#endif // LONGINT

