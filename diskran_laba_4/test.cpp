#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
int main()
{
    std::string text;
    std::getline(std::cin, text, '\0');
    for(size_t i = 0; i < text.size(); ++i)
    {
    	std::cout<<text[i]<<" = "<<int(text[i])<<std::endl;
	}
    return 0;
}
