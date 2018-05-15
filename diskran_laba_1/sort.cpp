#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <memory.h>
//#include <string.h>
//#include <cstring>
#include "Element.h"

void sort(TElement* array, int& amount_of_elems)
{
    const int radix = 16;
    const int strLen = 32;
    TElement* A = new TElement [amount_of_elems];
    for(int digit = strLen - 1; digit >= 0; --digit)
    {
        int C[radix] = {0};
        for(int i = 0; i < amount_of_elems; ++i)
        {
            A[i] = array[i];
            int c = array[i].Buffer[digit];

            if (c >= '0' && c <= '9') c = c - '0';
            else c = c - 'a' + 10; // According to ASCII table

            ++C[c];
        }
        for(int i = 1; i < radix; ++i)
        {
            C[i] = C[i] + C[i - 1];
        }
        for(int i = amount_of_elems - 1; i >= 0; --i)
        {
            TElement val = A[i];
            int c = A[i].Buffer[digit];

            if (c >= '0' && c <= '9') c = c - '0';
            else c = c - 'a' + 10; // According to ASCII table

            int position = C[c] - 1;
            array[position] = val;
            --C[c];
        }
    }
    delete[] A;

}
