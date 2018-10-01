#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
std::vector<int> Find(const std::string& pattern, const std::string& text)
{
    std::vector<int> res;
    for(int i = 0; i < text.size(); ++i)
    {
        int k = i;
        for(int j = 0; j < pattern.size(); ++j)
        {
            if(text[k] == pattern[j])
                ++k;
            else
                break;
        }
        if(i - k == pattern.size() - 1)
            res.push_back(i);
    }
    return res;
}
int main()
{
    std::string text;
    std::string pattern;
    std::cin>>text;
    size_t n = 1;
    std::string buf;
    while(std::cin>>pattern)
    {
        std::vector<int> res = Find(pattern, text);
        if(!res.empty())
        {
            std::cout<<n<<": ";
            for(auto i : res)
                std::cout<<res[i]<<", ";
        }
        ++n;
    }
    return 0;
}