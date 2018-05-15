#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "Element.h"
//#include <string.h>
int const W_EOF = 26; // End of file code in windows
TElement::TElement()
{
    pointer_key = NULL;
    pointer_value = NULL;
}
void TElement::print()
{
    if(pointer_key != NULL) {pointer_key->print();}
    else return;
    printf("\t");
    printf("%llu\n", *(pointer_value));
    //std::cout<<" "<<*(pointer_value)<<std::endl;
}

int TElement::get_char(int position)
{
    return key.get_char(position);
}
void TElement::set_char(int position, int ch)
{
    key.set_char(position, ch);
}
void TElement::set_pointer_value(unsigned long long int* val_ptr)
{
    pointer_value = val_ptr;
}
unsigned long long int* TElement::get_pointer_value()
{
    return &value;
}
void TElement::set_pointer_key(TString* key_ptr)
{
    pointer_key = key_ptr;
}
TString* TElement::get_pointer_key(void)
{
    return &key;
}
bool TElement::input(int& amount_of_elems)
{
    int ch = getchar();
    if(ch == EOF || ch == W_EOF ) return false;
    else ungetc(ch, stdin);
    key.write_str();
    scanf("%llu", &value);
    pointer_key = &key;
    pointer_value = &value;
    ++amount_of_elems;
    ch = getchar();
    if(ch == EOF || ch == W_EOF ) return false;
    return true;
}
TElement::~TElement()
{
    //std::cout<<"element deleted!"<<std::endl;
}

