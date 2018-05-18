#include <iostream>
#include <string>
int main()
{
    std::string s;
    getline(std::cin, s);
    for(int i = 0; i < s.size(); ++i)
    {
        std::cout<<s[i]<<" "<<(int)s[i]<<std::endl;
    }
    std::cin.get();
    return 0;
}