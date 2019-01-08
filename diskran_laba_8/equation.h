#ifndef LAB8_EQUATION_H
#define LAB8_EQUATION_H


#include <cstdio>
#include <vector>
#include <iostream>
#include <limits>
typedef double value;

class Equation {
private:
    std::size_t mCost;
    value *mVectorData;
    std::size_t mIndex;
    std::size_t size;
public:
    static const std::size_t INFINITY = std::numeric_limits<std::size_t>::max();
    explicit Equation();
    explicit Equation(const std::size_t& size, const std::size_t& index);
    explicit Equation(value *copyAdditive, const std::size_t &cost);
    explicit Equation(const Equation& mCopy);

    std::size_t getCost() const;
    void setCost(const std::size_t &mCost);

    value* getVectorData() const;
    void setVectorData(value* vectorData);

    void Print();

    friend std::vector<std::size_t> FindMinCost(Equation **mMatrix, const std::size_t& size,
                                                const std::size_t& columns);
    friend std::istream& operator>>(std::istream &is, Equation& eq);
    friend std::istream& operator>>(std::istream &is, Equation* eq);
    friend void Swap(Equation *&line1, Equation *&line2);
    friend void SimplificationMatrixGauss(Equation **mMatrix, const std::size_t& n,
                                          const std::size_t &columns, const std::size_t &currentPoint);
    ~Equation();
};


#endif //LAB8_EQUATION_H
