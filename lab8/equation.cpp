


#include "equation.h"

Equation::Equation() {
    this->mCost = 0;
}

Equation::Equation(value *copyAdditive,
                            const std::size_t &cost) {
    this->mVectorData = copyAdditive;
    this->mCost = cost;
}

Equation::Equation(const std::size_t &size,
                            const std::size_t& index) {
    this->mVectorData = new value[size];
    this->size = size;
    this->mIndex = index;

}

Equation::Equation(const Equation &mCopy) {
    this->mCost = mCopy.mCost;
    this->mVectorData = mCopy.mVectorData;
}

Equation::~Equation() {
    delete [] mVectorData;
}

std::size_t Equation::getCost() const {
    return mCost;
}
void Equation::setCost(const std::size_t &cost) {
    this->mCost = cost;
}

value* Equation::getVectorData() const {
    return mVectorData;
}

void Equation::setVectorData(value *vectorData) {
    this->mVectorData = vectorData;
}

std::vector<std::size_t> FindMinCost(Equation **mMatrix,
                                     const std::size_t& size,
                                     const std::size_t& columns) {

    std::vector<bool> minCostAnswerBool(size);
    for (std::size_t i = 0; i < columns; i++) {

        std::size_t minCost = Equation::INFINITY;
        std::size_t minFoodSubstance = Equation::INFINITY;
        for (std::size_t j = i; j < size; j++) {
            if (mMatrix[j]->mVectorData[i] != 0.0 && minCost > mMatrix[j]->getCost()) {
                minCost = mMatrix[j]->getCost();
                minFoodSubstance = j;
            }
        }

        if (minFoodSubstance == Equation::INFINITY) {
            return std::vector<std::size_t>(0);
        }

        Swap(mMatrix[i], mMatrix[minFoodSubstance]);

        minCostAnswerBool[mMatrix[i]->mIndex] = true;
        SimplificationMatrixGauss(mMatrix, size, columns, i);

    }
    std::vector<std::size_t> minCostAnswerInt(columns);
    std::size_t currentIndex = 0;
    for (std::size_t i = 0; i < size; i++) {
        if (minCostAnswerBool[i]) {
            minCostAnswerInt[currentIndex++] = i + 1;
        }
    }
    return minCostAnswerInt;
}

void SimplificationMatrixGauss(Equation **mMatrix, const std::size_t &n,
                               const std::size_t &columns, const std::size_t &currentPoint) {
    for (std::size_t i = currentPoint + 1; i < n; ++i) {
        double c = mMatrix[i]->mVectorData[currentPoint] /
                                        mMatrix[currentPoint]->mVectorData[currentPoint];

        for (std::size_t j = currentPoint; j < columns; ++j) {
            mMatrix[i]->mVectorData[j] -= mMatrix[currentPoint]->mVectorData[j] * c;
        }
    }
}

std::istream& operator >> (std::istream &is, Equation& eq) {
    for (std::size_t i = 0; i < eq.size; i++) {
        is >> eq.mVectorData[i];
    }
    is >> eq.mCost;
    return is;
}


std::istream& operator >> (std::istream &is, Equation* eq) {
    for (std::size_t i = 0; i < eq->size; i++) {
        is >> eq->mVectorData[i];
    }
    is >> eq->mCost;
    return is;
}


void Equation::Print() {
   // std::cout << "\nVECTOR:\n";
    for (std::size_t i = 0; i < size; i++) {
        std::cout << mVectorData[i] << "\t";
    }
    std::cout << std::endl;// << "COST = " << mCost << " USED = " << mUsed << std::endl;

}


void Swap(Equation *&line1, Equation *&line2) {
    Equation *tmp = line1;
    line1 = line2;
    line2 = tmp;
}
