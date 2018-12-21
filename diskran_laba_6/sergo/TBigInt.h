#ifndef LAB6_TBIGINT_H
#define LAB6_TBIGINT_H
#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

class TBigInt {
public:
    explicit TBigInt();
    explicit TBigInt(std::size_t copy);
    explicit TBigInt(std::size_t nRadix, std::size_t nBase = DEFAULT_DEGREE_BASE);
    explicit TBigInt(const std::string &nLine, const std::size_t nBase = DEFAULT_DEGREE_BASE);
    explicit TBigInt(std::vector<int>  &otherNum, std::size_t nBase = DEFAULT_DEGREE_BASE);
    TBigInt(const TBigInt &otherNum);


    TBigInt operator+(const TBigInt &otherNum) const;

    TBigInt operator-(const TBigInt &otherNum) const;

    TBigInt operator*(const TBigInt &otherNum) const;
    TBigInt operator*(const int     &otherNum) const;
    TBigInt operator^(const TBigInt &otherNum) const;


    TBigInt operator/(const TBigInt &otherNum) const;

    TBigInt Karatsuba(const TBigInt &otherNum) const;

    friend bool operator>(const  TBigInt &num1, const TBigInt &num2);
    friend bool operator<(const  TBigInt &num1, const TBigInt &num2);
    friend bool operator==(const TBigInt &num1, const TBigInt &num2);

    friend bool operator==(const TBigInt &num1, std::size_t num2);

    friend std::ostream& operator<<(std::ostream& os, const TBigInt& outNum);
    std::size_t size() const;

//    bool isNull() const;

    virtual ~TBigInt();

private:
    TBigInt CopyHalf(std::size_t from, std::size_t to) const;
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



#endif //LAB6_TBIGINT_H
