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
                    ans = std::max(ans, static_cast<const int &>((int)(x - i) * (y - j)));
                    y = j;
                }
            }
        }
    }
    return ans;
}

std::size_t TMatrix::FindMaxSubMatrixFast(const std::size_t type) {
    int ans = 0;
    std::vector<int> d (m, -1), d1 (m), d2 (m);
    std::stack<int> st;
    for (int i=0; i<n; ++i) {
        for (int j=0; j<m; ++j)
            if (mData[i][j] == 1)
                d[j] = i;
        while (!st.empty()) st.pop();
        for (int j=0; j<m; ++j) {
            while (!st.empty() && d[st.top()] <= d[j])  st.pop();
            d1[j] = st.empty() ? -1 : st.top();
            st.push (j);
        }
        while (!st.empty()) st.pop();
        for (int j=m-1; j>=0; --j) {
            while (!st.empty() && d[st.top()] <= d[j])  st.pop();
            d2[j] = st.empty() ? m : st.top();
            st.push (j);
        }
        for (int j=0; j<m; ++j)
            ans = std::max (ans, (i - d[j]) * (d2[j] - d1[j] - 1));
    }
    return ans;
}