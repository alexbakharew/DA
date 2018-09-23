#include <iostream>
#include <string>
void SloySort(const std::string& pattern, const std::string& text)
{
    for(int i = 0; i < text.size() - pattern.size(); ++i)
    {
        int k = i;
        for(int j = 0; j < pattern.size(); ++j)
        {
            if(text[k] == pattern[j])
                ++k;
            else
                break;
        }
        if(k == i + pattern.size())
            std::cout<<"Match\n";
    }
}
int main()
{
    std::string pattern;
    std::string text;
    long val;
    while(std::cin.get() != '\n')
    {
        std::cin.unget();
        std::cin>>val;
        pattern += std::to_string(val) + " ";
    }
    while(pattern.back() == ' ')
        pattern.pop_back();
    while(std::cin>>val)
    {
        text += std::to_string(val);
        int ch;
        ch = std::cin.get();
        if(ch == ' ')    text += " ";
        else    text += "\n";
    }
    SloySort(pattern, text);
    return 0;
}