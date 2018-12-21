 #include <cmath>
#include "TBigInt.h"
#include <cstdio>
TBigInt::TBigInt() {
    base = DEFAULT_DEGREE_BASE;
    fullBase = DEFAULT_FULL_BASE;
}


void TBigInt::DeleteZeros() {
    while (this->size() > 1 && data.back() == 0 ) {
        data.pop_back();
    }
}

TBigInt::TBigInt(std::size_t mCopy) {
    base = DEFAULT_DEGREE_BASE;
    fullBase = DEFAULT_FULL_BASE;
    while (mCopy != 0) {
        data.push_back(mCopy % fullBase);
        mCopy /= fullBase;
    }
}

TBigInt::TBigInt(std::size_t nRadix, std::size_t nBase) {
    data.resize(nRadix ? nRadix : 1, 0);
    base = nBase ? nBase : DEFAULT_DEGREE_BASE;
    fullBase = static_cast<size_t>(std::pow(DEFAULT_BASE, base));
}

TBigInt::TBigInt(const std::string &nLine, const std::size_t nBase) {
    base = nBase ? nBase : DEFAULT_DEGREE_BASE;
    fullBase = static_cast<size_t>(std::pow(DEFAULT_BASE, base));

    for (long int row = nLine.size(); 0 <= row; row -= base) {
        if (row < base) {
            data.push_back(atoi(nLine.substr(0, row).c_str()));
        } else {
            data.push_back(atoi(nLine.substr(row - base, base).c_str()));
        }
    }
    DeleteZeros();
}

TBigInt::TBigInt(std::vector<int> &otherNum, std::size_t nBase ) {
    this->data = otherNum;
    base = nBase ? nBase : DEFAULT_DEGREE_BASE;
    fullBase = static_cast<size_t>(pow(DEFAULT_BASE, base));
}

TBigInt::TBigInt(const TBigInt &otherNum) {
    base = otherNum.base;
    fullBase = otherNum.fullBase;
    data = otherNum.data;
}

//bool TBigInt::isNull()  const {
//    return size() == 1 && !data[0];
//}


bool operator>(const TBigInt &num1, const TBigInt &num2) {
    if (num1.size() > num2.size() ) {
        return true;
    }
    if (num1.size()  < num2.size()) {
        return false;
    }
    for (int i = num1.size() - 1; i >= 0; i--) {
        if (num1.data[i] > num2.data[i]) {
            return true;
        }
        if (num1.data[i] < num2.data[i]) {
            return false;
        }
    }
    return false;
}

bool operator<(const TBigInt &num1, const TBigInt &num2) {
    if (num1.size() > num2.size()) {
        return false;
    }
    if (num1.size() < num2.size()) {
        return true;
    }
    for (int i = num1.size() - 1; i >= 0; i--) {
        if (num1.data[i] > num2.data[i]) {
            return false;
        }
        if (num1.data[i] < num2.data[i]) {
            return true;
        }
    }
    return false;
}

bool operator==(const TBigInt &num1, std::size_t num2) {
    if (!num2 && num1.size() == 1 && num1.data[0] == 0 ) {
        return true;
    }

    std::vector<int>::const_iterator it = num1.data.begin();

    while (num2 > 0) {
        std::size_t row = num2 % num1.fullBase;
        num2 /= num1.fullBase;
        if (it == num1.data.end() || row != *it) {
            return false;
        }
        it++;
    }
    return num1.data.end() == it ? true : false;
}

std::ostream& operator<<(std::ostream& os, const TBigInt& outNum) {
    std::size_t length = outNum.size();
    os << outNum.data[length-1];
    for(int i = length - 2; i >= 0; --i ) {
        os << std::setfill('0') << std::setw(static_cast<int>(outNum.base)) << outNum.data[i];
    }
    return os;
}


bool operator==(const TBigInt &num1, const TBigInt &num2) {
    if (num1.size() != num2.size()) {
        return false;
    }
    for (int i = num1.size() - 1; i >= 0; i--) {
        if (num1.data[i] != num2.data[i]) {
            return false;
        }
    }
    return true;
}

TBigInt TBigInt::operator+(const TBigInt &otherNum) const {
    if (this->base != otherNum.base) {
        std::cerr << "Error: values have different base\n";
        exit(EXIT_FAILURE);
    }
    std::size_t  bigLength = std::max(this->size(), otherNum.size());

    TBigInt result(bigLength + 1, base);

    bool incNextRow = false;

    for (std::size_t i = 0; i < bigLength || incNextRow; ++i) {

        int currentRow = incNextRow;

        if (i < this->size()) {
            currentRow += this->data[i];
        }

        if (i < otherNum.size()) {
            currentRow += otherNum.data[i];
        }

        incNextRow = currentRow >= fullBase;

        if (incNextRow) currentRow -= fullBase;
        result.data[i] = currentRow;
    }
    result.DeleteZeros();
    return result;
}

TBigInt TBigInt::operator-(const TBigInt &otherNum) const {
    if (this->base != otherNum.base) {
        std::cerr << "Error: values have different base\n";
        exit(EXIT_FAILURE);
    }

    std::size_t  bigLength = this->size();
    TBigInt result(bigLength, base);
    bool decNextRow = false;

    for (std::size_t i = 0; i < bigLength || decNextRow; i++)
    {
        int currentRow = this->data[i] - decNextRow;

        if (i < otherNum.size()){
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

TBigInt TBigInt::operator*(const TBigInt &otherNum) const {
    if (this->base != otherNum.base) {
        std::cerr << "Error: values have different base\n";
        exit(EXIT_FAILURE);
    }
    if (otherNum == 0 || this == 0) {
        return TBigInt("0");
    }
    std::size_t lengthLeftOperand  = this->size();
    std::size_t lengthRightOperand = otherNum.size();

    TBigInt result(lengthLeftOperand + lengthRightOperand, this->base);

    for(std::size_t i = 0; i < lengthRightOperand; ++i) {
        if (otherNum.data[i] == 0) {
            continue;
        }
        int incNextRow = 0;
        for(std::size_t j = 0; j < lengthLeftOperand; ++j) {
            long long int tmp = this->data[j] * otherNum.data[i] +
                              result.data[i + j] + incNextRow;
            incNextRow = tmp / fullBase;
            result.data[i + j] = tmp % fullBase;
            if (result.data[i+j] < 0) {
                std::cout << i << " " << j << " Error\n";
            }
        }
        result.data[i + lengthLeftOperand] = incNextRow;
    }
    result.DeleteZeros();
    return result;
}

TBigInt TBigInt::Karatsuba(const TBigInt& otherNum) const{
    if (this->size() < 4 || otherNum.size() < 4) {
        return (*this) * otherNum;
    }
    std::size_t mid = std::max(this->size(), otherNum.size())/2;
    std::size_t begin = 0;

    TBigInt x0 = CopyHalf(begin,  mid);
    TBigInt x1 = CopyHalf(mid, this->size());
    TBigInt y0 = otherNum.CopyHalf(begin,  mid);;
    TBigInt y1 = otherNum.CopyHalf(mid, otherNum.size());


    TBigInt x0y0 = x0.Karatsuba(y0);
    TBigInt x1y1 = x1.Karatsuba(y1);
    TBigInt x0x1y0y1 = (x0 + x1).Karatsuba(y0 + y1);

    return x0y0 + (x0x1y0y1 - x0y0 - x1y1)*std::pow(DEFAULT_BASE, mid) + x1y1*std::pow(DEFAULT_BASE, 2*mid);
}

TBigInt TBigInt::CopyHalf(std::size_t from, std::size_t to) const {
    if (from < to) {
        return TBigInt({this->data.begin() + from, this->data.begin() + to}, base);
    } else {
        return TBigInt({0}, base);
    }
}

TBigInt TBigInt::operator^(const TBigInt &otherNum) const {
    if ((*this == 1) || otherNum == 0) {
        return TBigInt("1");
    }
    if (otherNum == 1) {
        return *this;
    }

    if(otherNum.data[0] % 2 == 0) {

        TBigInt res = (*this) ^ (otherNum / TBigInt("2", base));

        return res * res;
    } else {

        return (*this) * ((* this) ^ (otherNum - TBigInt("1")));
    }
}


TBigInt TBigInt::operator/(const TBigInt &otherNum) const {
    TBigInt res(this->size(), base);
    register TBigInt curValue;
    for (int i = this->size() - 1; i >= 0; i--)
    {
        curValue.ShiftUp(data[i]);
        // подбираем максимальное число x, такое что b * x <= curValue
        int m;
        int mid = 0;
        int l = 0, r = res.fullBase;
        if (curValue < otherNum) {
            continue;
        }
        while (l <= r) {
            m = (l + r) / 2;
            TBigInt cur = otherNum * m;
            if (!(cur > curValue)) {
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


void TBigInt::ShiftUp(const int &value) {
    data.insert(data.begin(), value);
    DeleteZeros();
}

TBigInt TBigInt::operator*(const int &otherNum) const {
    TBigInt result = *this;
    int incNextRow = 0;

    for (size_t i = 0; i < this->size() || incNextRow; ++i) {
        if (i == result.size())
            result.data.push_back(0);
        std::size_t currentRow = static_cast<size_t>(incNextRow + result.data[i] * otherNum);
        result.data[i] = (int)(currentRow % fullBase);
        incNextRow = (int)(currentRow / fullBase);
    }
    return result;
}

std::size_t TBigInt::size() const {
    return data.size();
}

TBigInt::~TBigInt() {
    data.shrink_to_fit();
}
