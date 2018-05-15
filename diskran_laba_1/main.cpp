//#include <string.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Element.h"
#include "sort.h"
int main(int argc, char *argv[])
{
    int size_of_array = 1; // default value
    int amount_of_elems = 0;
    TElement* array = new TElement[size_of_array]; // array of elems
    while(1)
    {
        char ch = getchar();
        if(ch == EOF || ch == '\0')
        {
            break;
        }
        else
        {
            ungetc(ch, stdin);
        }
        if(amount_of_elems == size_of_array)
        {
            TElement* tmp_buffer = new TElement[size_of_array];
            memcpy(tmp_buffer, array, size_of_array*sizeof(TElement));
            array = new TElement[size_of_array * 2];
            memcpy(array, tmp_buffer, size_of_array*sizeof(TElement));
            size_of_array *= 2;
            delete[] tmp_buffer;
        }
        scanf("%s", array[amount_of_elems].Buffer);
        scanf("%llu", &array[amount_of_elems].n);
        ++amount_of_elems;
        getchar();
    }
    sort(array, amount_of_elems);
    for(int i = 0; i < amount_of_elems; ++i)
    {
        printf("%s\t", array[i].Buffer);
        printf("%llu\n", array[i].n);
    }
    delete[] array;
    return 0;
}
