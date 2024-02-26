#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>
#include <limits>
class TLongInt
{
public:
    explicit TLongInt();
    explicit TLongInt(std::size_t copy);
    explicit TLongInt(std::size_t nRadix, std::size_t nBase = DEFAULT_DEGREE_BASE);
    explicit TLongInt(const std::string &nLine, const std::size_t nBase = DEFAULT_DEGREE_BASE);
    explicit TLongInt(std::vector<int>  &otherNum, std::size_t nBase = DEFAULT_DEGREE_BASE);
    TLongInt(const TLongInt &otherNum);

    TLongInt operator + (const TLongInt &otherNum) const;
    TLongInt operator - (const TLongInt &otherNum) const;
    TLongInt operator * (const TLongInt &otherNum) const;
    TLongInt operator * (const int& otherNum) const;
    TLongInt operator ^ (const TLongInt &otherNum) const;
    TLongInt operator / (const TLongInt &otherNum) const;

    friend bool operator>(const  TLongInt &num1, const TLongInt &num2);
    friend bool operator<(const  TLongInt &num1, const TLongInt &num2);
    friend bool operator==(const TLongInt &num1, const TLongInt &num2);
    friend bool operator==(const TLongInt &num1, size_t num2);

    friend std::ostream& operator<<(std::ostream& os, const TLongInt& outNum);
    std::size_t size() const;

    ~TLongInt();

private:
    void ShiftUp(const int &value);
    void DeleteZeros();
protected:
    std::vector<int> data;
    std::size_t base;
    std::size_t fullBase;
    static const std::size_t DEFAULT_DEGREE_BASE = 4;
    static const std::size_t DEFAULT_FULL_BASE = 10000;
    static const std::size_t DEFAULT_BASE = 10;
};

