#ifndef STRING
#define STRING
#include <iostream>
class TElement;
class TString
{
public:
    TString();
    ~TString();
    char operator[](size_t);
    char Buffer[33];
private:
};
#endif // STRING
