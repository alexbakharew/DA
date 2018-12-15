#include <stack>
#include "TMatrix.h"

TMatrix::TMatrix(const TMatrix &mCopy) {
    mData = mCopy.mData;
    m = mCopy.m;
    n = mCopy.n;
}

TMatrix::TMatrix(std::size_t n, std::size_t m) {
    this->n = n;
    this->m = m;
    mData.resize(n);
    for (std::size_t i = 0; i < n; i++) {
        mData[i].resize(m);
    }
}

std::ostream& operator<<(std::ostream& os, const TMatrix& outMatrix) {
    for (auto i : outMatrix.mData) {
        for (auto j : i) {
            os << j << "\t";
        }
        os << std::endl;
    }
    return os;
}

std::istream& operator>>(std::istream& is, TMatrix& inMatrix) {
    for (std::size_t i = 0; i < inMatrix.n; i++) {
        std::string line;
        is >> line;
        for (std::size_t j = 0; j < inMatrix.m; j++) {
            inMatrix.mData[i][j] = line[j] - '0';
        }

    }
    return is;
}

std::size_t TMatrix::FindMaxSubMatrixTrivial(const std::size_t type) {
    int ans = 0;
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < m; j++) {
            std::size_t right = m;
            std::size_t down = n;
            if (mData[i][j] == type) {
                std::size_t x = i;
                std::size_t y = j;
                while (x < down && mData[x][y] == type) {
                    while (y < right && mData[x][y] == type) {
                        y++;
                    }
                    right = y;
                    x++;
                    ans = std::max(ans, static_cast<const int &>((x - i) * (y - j)));
                    y = j;
                }
            }
        }
    }
    return ans;
}

std::size_t TMatrix::FindMaxSubMatrixFast(const std::size_t type) {
    int ans = 0;
    std::vector<int> dp (m, INFINITY), indexLeft(m), indexRight(m);
    std::stack<int> stack;
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < m; j++) {
            if (mData[i][j] != type) {
                dp[j] = i;
            }
        }

        ClearStack(stack);
        for (int j = 0; j < m; j++) {
            while (!stack.empty() && dp[ stack.top() ] <= dp[j]) {
                stack.pop();
            }
            indexLeft[j] = stack.empty() ? INFINITY : stack.top();
            stack.push(j);
        }

        ClearStack(stack);
        for (int j = m - 1; j >= 0; j--) {
            while (!stack.empty() && dp[stack.top()] <= dp[j]) {
                stack.pop();
            }
            indexRight[j] = stack.empty() ? m : stack.top();
            stack.push(j);
        }

        for (int j = 0; j < m; j++)
            ans = std::max(ans, (i - dp[j])*(indexRight[j] - indexLeft[j] - 1));
    }
    return ans;
}

void ClearStack(std::stack<int> &tStack) {
    while (!tStack.empty()) {
        tStack.pop();
    }
}