#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdio>
#include "TMatrix.h"

double FindMaxSubMatrixTrivialTime(TMatrix& matrix) {
	clock_t start = clock();
	matrix.FindMaxSubMatrixTrivial(0);
	clock_t finish = clock();
	return (double) (finish - start)/CLOCKS_PER_SEC;
}



double FindMaxSubMatrixFastTime(TMatrix& matrix) {
	clock_t start = clock();
	matrix.FindMaxSubMatrixFast(0);
	clock_t finish = clock();
	return (double) (finish - start)/CLOCKS_PER_SEC;
}

int main(int argc, char *argv[]) {
	FILE* fout_trivial;
	FILE* fout_fast;
	FILE* fout_count;

	fout_count = fopen("./count", "a+");
	fout_trivial = fopen("./trivial.txt", "a+");
	fout_fast = fopen("./fast.txt", "a+");

    int /*std::size_t*/ n, m;
    std::cin >> n >> m;
    TMatrix matrix(n, m);
    std::cin >> matrix;

    fprintf( fout_fast, "%0.15f\n", FindMaxSubMatrixFastTime(matrix) );
    fprintf( fout_trivial, "%0.15f\n", FindMaxSubMatrixTrivialTime(matrix) );
    fprintf( fout_count, "%d\n", n*m );

    fclose(fout_trivial);
    fclose(fout_fast);
    fclose(fout_count);
    return 0;
}
