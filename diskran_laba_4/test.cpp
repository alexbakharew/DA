#include <iostream>
#include <vector>
#include <string>
struct word
{
    size_t begin;
    size_t n;
    size_t line;
};
int main()
{
    std::vector<word> wordsMap;
    std::string text;
    int val;
    size_t i = 0;
    size_t line = 1;
    size_t n = 1;
    int ch = std::cin.get();
    while(ch == ' ' || ch == '\n')
    {
        std::cout<<"he\n";
        if(ch == '\n')
            ++line;
        ++i;
        ch = std::cin.get();
    }
    if(ch == '\0' || ch == EOF)
        return 0;
    if(ch >= '0' && ch <= '9')
        std::cin.unget(), ch = 0;
    while(std::cin>>val)
    {
        std::string tmpStr = std::to_string(val);
        text += tmpStr + " ";
        word tmpWord;
        if(i == 0)
        {
            tmpWord = {i, n, line};
            i += tmpStr.size();
        }
        else
        {
            tmpWord = {i + 1, n, line};
            i += tmpStr.size() + 1;            
        }
        wordsMap.push_back(tmpWord);
        ++n;
        ch = std::cin.get(); // skip spase
        ch = std::cin.get();
        while(ch == ' ' || ch == '\n')
        {
            if(ch == '\n')
            {
                ++line;
                n = 1;
            }
            ++i;
            ch = std::cin.get();
        }   
        if(ch >= '0' && ch <= '9')
            std::cin.unget(), ch = 0;
    }
    text.pop_back();
    std::cout<<text<<std::endl;
    for(int k = 0; k < text.size(); ++k)
    {
        std::cout<<k;
    }
    std::cout<<"'----------------------\n";
    for(int k = 0; k < wordsMap.size(); ++k)
    {
        std::cout<<"word"<<k + 1<<std::endl;
        std::cout<<wordsMap[k].begin<<" "<<wordsMap[k].line<<" "<<wordsMap[k].n<<std::endl;
        std::cout<<"-------------------------------------------------------------------------\n";
    }
    return 0;
}