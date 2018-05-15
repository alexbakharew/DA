#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
class TElement
{
public:
    TElement(){}
    ~TElement(){}
    friend std::istream& operator>>(std::istream&, const TElement&);
    friend std::ostream& operator<<(std::ostream&, const TElement&);
    bool operator >(const TElement&);
    bool operator <(const TElement&);
    bool operator ==(const TElement&);
    unsigned long long int* GetN();
    char* GetBuff();
private:
    char Buffer[33];
    unsigned long long int N;
};
bool TElement::operator<(const TElement& n1)
{
    if(strncmp(n1.Buffer, this->Buffer, 33) < 0) return true;
    else return false;
}
bool TElement::operator>(const TElement& n1)
{
    if(strncmp(n1.Buffer, this->Buffer, 33) > 0) return true;
    else return false;
}
bool TElement::operator==(const TElement& n1)
{
    if(strncmp(n1.Buffer, this->Buffer, 33) == 0) return true;
    else return false;
}
std::istream& operator>>(std::istream& input, TElement& n)
{
    char* Buff = n.GetBuff();
    input>>Buff;
    input.get();
    auto N = n.GetN();
    input>>*N;
    //input.get(); Commented for \0 recognition
    return input;
}
std::ostream& operator<<(std::ostream& output, const TElement& n)
{
    output<<n.Buffer;
    output<<"\t";
    output<<n.N;
    return output;
}
unsigned long long int* TElement::GetN()
{
    return &N;
}
char* TElement::GetBuff()
{
    return Buffer;
}
int main()
{
    std::vector<TElement> array;
    while(!std::cin.eof())
    {
        //std::cin.unget();
        TElement tmp;
        std::cin>>tmp;
        array.push_back(tmp);
        // std::cout<<"OK\n";
    }
    std::sort(array.begin(), array.end());
    for(int i = 0; i < array.size() - 1; ++i)
    {
        std::cout<<array[i]<<std::endl;
    }
}