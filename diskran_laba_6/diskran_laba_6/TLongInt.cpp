 #include <cmath>
#include "TLongInt.h"
#include <cstdio>
TLongInt::TLongInt()
{
    base = DEFAULT_DEGREE_BASE;
    fullBase = DEFAULT_FULL_BASE;
}


void TLongInt::DeleteZeros()
{
    while (this->size() > 1 && data.back() == 0 )
    {
        data.pop_back();
    }
}

TLongInt::TLongInt(std::size_t mCopy)
{
    base = DEFAULT_DEGREE_BASE;
    fullBase = DEFAULT_FULL_BASE;
    while (mCopy != 0)
    {
        data.push_back(mCopy % fullBase);
        mCopy /= fullBase;
    }
}

TLongInt::TLongInt(std::size_t nRadix, std::size_t nBase)
{
    data.resize(nRadix ? nRadix : 1, 0);
    base = nBase ? nBase : DEFAULT_DEGREE_BASE;
    fullBase = static_cast<size_t>(std::pow(DEFAULT_BASE, base));
}

TLongInt::TLongInt(const std::string &nLine, const std::size_t nBase)
{
    base = nBase ? nBase : DEFAULT_DEGREE_BASE;
    fullBase = static_cast<size_t>(std::pow(DEFAULT_BASE, base));

    for (long int row = nLine.size(); 0 <= row; row -= base)
    {
        if (row < base)
        {
            data.push_back(atoi(nLine.substr(0, row).c_str()));
        }
        else
        {
            data.push_back(atoi(nLine.substr(row - base, base).c_str()));
        }
    }
    DeleteZeros();
}

TLongInt::TLongInt(std::vector<int> &otherNum, std::size_t nBase )
{
    this->data = otherNum;
    base = nBase ? nBase : DEFAULT_DEGREE_BASE;
    fullBase = static_cast<size_t>(pow(DEFAULT_BASE, base));
}

TLongInt::TLongInt(const TLongInt &otherNum)
{
    base = otherNum.base;
    fullBase = otherNum.fullBase;
    data = otherNum.data;
}

bool operator>(const TLongInt &num1, const TLongInt &num2)
{
    if (num1.size() > num2.size() )
    {
        return true;
    }
    if (num1.size()  < num2.size())
    {
        return false;
    }
    for (int i = num1.size() - 1; i >= 0; i--) {
        if (num1.data[i] > num2.data[i])
        {
            return true;
        }
        if (num1.data[i] < num2.data[i])
        {
            return false;
        }
    }
    return false;
}

bool operator<(const TLongInt &num1, const TLongInt &num2) {
    if (num1.size() > num2.size())
    {
        return false;
    }
    if (num1.size() < num2.size())
    {
        return true;
    }
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        if (num1.data[i] > num2.data[i])
        {
            return false;
        }
        if (num1.data[i] < num2.data[i])
        {
            return true;
        }
    }
    return false;
}

bool operator==(const TLongInt &num1, std::size_t num2)
{
    if (!num2 && num1.size() == 1 && num1.data[0] == 0 )
    {
        return true;
    }

    std::vector<int>::const_iterator it = num1.data.begin();

    while (num2 > 0) {
        std::size_t row = num2 % num1.fullBase;
        num2 /= num1.fullBase;
        if (it == num1.data.end() || row != *it)
        {
            return false;
        }
        it++;
    }
    return num1.data.end() == it ? true : false;
}

std::ostream& operator<<(std::ostream& os, const TLongInt& outNum)
{
    std::size_t length = outNum.size();
    os << outNum.data[length-1];
    for(int i = length - 2; i >= 0; --i )
    {
        os << std::setfill('0') << std::setw(static_cast<int>(outNum.base)) << outNum.data[i];
    }
    return os;
}


bool operator==(const TLongInt &num1, const TLongInt &num2)
{
    if (num1.size() != num2.size())
    {
        return false;
    }
    for (int i = num1.size() - 1; i >= 0; i--)
    {
        if (num1.data[i] != num2.data[i])
        {
            return false;
        }
    }
    return true;
}

TLongInt TLongInt::operator+(const TLongInt &otherNum) const
{
    if (this->base != otherNum.base)
    {
        std::cerr << "Error: values have different base\n";
        exit(EXIT_FAILURE);
    }
    std::size_t  bigLength = std::max(this->size(), otherNum.size());

    TLongInt result(bigLength + 1, base);

    bool incNextRow = false;

    for (std::size_t i = 0; i < bigLength || incNextRow; ++i)
    {

        int currentRow = incNextRow;

        if (i < this->size())
        {
            currentRow += this->data[i];
        }

        if (i < otherNum.size())
        {
            currentRow += otherNum.data[i];
        }

        incNextRow = currentRow >= fullBase;

        if (incNextRow) currentRow -= fullBase;
        result.data[i] = currentRow;
    }
    result.DeleteZeros();
    return result;
}

TLongInt TLongInt::operator-(const TLongInt &otherNum) const
{
    if (this->base != otherNum.base)
    {
        std::cerr << "Error: values have different base\n";
        exit(EXIT_FAILURE);
    }

    std::size_t  bigLength = this->size();
    TLongInt result(bigLength, base);
    bool decNextRow = false;

    for (std::size_t i = 0; i < bigLength || decNextRow; i++)
    {
        int currentRow = this->data[i] - decNextRow;

        if (i < otherNum.size())
        {
            currentRow -= otherNum.data[i];
        }
        decNextRow = currentRow < 0;

        if (decNextRow) currentRow += fullBase;

        result.data[i] = currentRow;
    }
    //RemoveLeadingZero
    result.DeleteZeros();
    return result;
}

TLongInt TLongInt::operator*(const TLongInt &otherNum) const
{
    if (this->base != otherNum.base)
    {
        std::cerr << "Error: values have different base\n";
        exit(EXIT_FAILURE);
    }
    if (otherNum == 0 || this == 0)
    {
        return TLongInt("0");
    }
    std::size_t lengthLeftOperand  = this->size();
    std::size_t lengthRightOperand = otherNum.size();

    TLongInt result(lengthLeftOperand + lengthRightOperand, this->base);

    for(std::size_t i = 0; i < lengthRightOperand; ++i)
    {
        if (otherNum.data[i] == 0)
        {
            continue;
        }
        int incNextRow = 0;
        for(std::size_t j = 0; j < lengthLeftOperand; ++j)
        {
            long long int tmp = this->data[j] * otherNum.data[i] +
                              result.data[i + j] + incNextRow;
            incNextRow = tmp / fullBase;
            result.data[i + j] = tmp % fullBase;
            if (result.data[i+j] < 0)
            {
                std::cout << i << " " << j << " Error\n";
            }
        }
        result.data[i + lengthLeftOperand] = incNextRow;
    }
    result.DeleteZeros();
    return result;
}

TLongInt TLongInt::operator^(const TLongInt &otherNum) const
{
    if ((*this == 1) || otherNum == 0)
    {
        return TLongInt("1");
    }
    if (otherNum == 1)
    {
        return *this;
    }

    if(otherNum.data[0] % 2 == 0)
    {
        TLongInt res = (*this) ^ (otherNum / TLongInt("2", base));
        return res * res;
    }
    else
    {

        return (*this) * ((* this) ^ (otherNum - TLongInt("1")));
    }
}


TLongInt TLongInt::operator/(const TLongInt &otherNum) const
{
    TLongInt res(this->size(), base);
    register TLongInt curValue;
    for (int i = this->size() - 1; i >= 0; i--)
    {
        curValue.ShiftUp(data[i]);
        // подбираем максимальное число x, такое что b * x <= curValue
        int m;
        int mid = 0;
        int l = 0, r = res.fullBase;
        if (curValue < otherNum)
        {
            continue;
        }
        while (l <= r) {
            m = (l + r) / 2;
            TLongInt cur = otherNum * m;
            if (!(cur > curValue))
            {
                l = m + 1;
                mid = m;
            }
            else
                r = m - 1;
        }
        res.data[i] = mid;
        curValue = curValue - otherNum * mid;
    }
    res.DeleteZeros();
    return res;
}


void TLongInt::ShiftUp(const int &value)
{
    data.insert(data.begin(), value);
    DeleteZeros();
}

TLongInt TLongInt::operator*(const int &otherNum) const
{
    TLongInt result = *this;
    int incNextRow = 0;

    for (size_t i = 0; i < this->size() || incNextRow; ++i)
    {
        if (i == result.size())
            result.data.push_back(0);
        std::size_t currentRow = static_cast<size_t>(incNextRow + result.data[i] * otherNum);
        result.data[i] = (int)(currentRow % fullBase);
        incNextRow = (int)(currentRow / fullBase);
    }
    return result;
}

std::size_t TLongInt::size() const
{
    return data.size();
}

TLongInt::~TLongInt() {}
