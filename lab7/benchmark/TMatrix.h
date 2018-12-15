//
// Created by bokoch on 3/12/18.
//

#ifndef LAB7_TMATRIX_H
#define LAB7_TMATRIX_H


#include <vector>
#include <iostream>

class TMatrix {
private:
    std::vector< std::vector<int> > mData;
    std::size_t n;
    std::size_t m;
public:
    explicit TMatrix(const TMatrix& mCopy);
    explicit TMatrix(std::size_t n, std::size_t m);
    std::size_t FindMaxSubMatrixFast(const std::size_t type);
    std::size_t FindMaxSubMatrixTrivial(const std::size_t type);
    friend std::ostream& operator<<(std::ostream& os, const TMatrix& outMatrix);
    friend std::istream& operator>>(std::istream& is, TMatrix& inMatrix);
    virtual ~TMatrix() = default;
};


#endif //LAB7_TMATRIX_H
