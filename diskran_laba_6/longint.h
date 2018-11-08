#ifndef LONGINT
#define LONGINT
#include <cstdlib>
#include <string>
#include <vector>
class TLongInt
{
public:
    TLongInt();
    TLongInt(int n);
    TLongInt(const std::string& number);
    ~TLongInt(){}
    void operator +=(const TLongInt& other);
    bool operator -=(const TLongInt& other);
    TLongInt operator *(const TLongInt& other);
    TLongInt operator /(const TLongInt& other);
    bool operator ==(const TLongInt& other);
    TLongInt pow(int n);
    // TODO - comparison between TLongInt and simple int
    bool operator <(const TLongInt& other);
    bool operator >(const TLongInt& other);
    void print();// Like in memory
    //void print_normal();// How it ought to be

    //friend std::ostream& operator<<(std::ostream& output, const TLongInt& number);
private:
    std::vector<long int> Data;
};

#endif // LONGINT

