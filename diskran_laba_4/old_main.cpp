#include <iostream>
#include <string>
#include <vector>
std::vector<size_t> prefix_function (std::string& s)
{
    size_t n =  s.length();
    std::vector<size_t> pi(n);
    for (size_t i = 1; i < n; ++i)
    {
        if(s[i] == '\n')
            s[i] = ' ';
        size_t j = pi[i - 1];
        while ((j > 0) && (s[i] != s[j]))
            j = pi[j - 1];
        if (s[i] == s[j])
            ++j;
        pi[i] = j;
     }
     return pi;
}
struct word
{
    size_t begin;
    size_t n;
    size_t line;
};

std::vector<word> Words(const std::string& s)
{
    std::vector<word> wordsMap;

    size_t line; 
    size_t n;
    if(s[0] == '\n')
    {
        line = 2;
        n = 1;
    }
    else
    {
        word init;
        wordsMap.push_back(init);// first and may be only one word in whole string
        wordsMap[0].begin = 0;
        wordsMap[0].line = 1;
        wordsMap[0].n = 1;
        line = 1;
        n = 2;
    }

    for(size_t i = 1; i < s.size(); ++i)
    {
        if(s[i] == '\n')
        {
            if(s[i + 1] == '\n')
            {
                ++line;
                continue;
            }
            ++line;
            n = 1;
            word tmp = {i + 1, n, line};
            wordsMap.push_back(tmp);
            ++n;
            continue;
        }
        if(s[i] == ' ')
        {
            if(s[i + 1] == ' ')
                break;
            word tmp = {i + 1, n, line};
            wordsMap.push_back(tmp);
            ++n;
            continue;
            
        }
    }
    return wordsMap;
}
std::vector<size_t> KMP(std::string& s, const size_t& size)
{
    std::vector<size_t> result;
    auto sp = prefix_function(s);
    for(size_t i = size; i < sp.size(); ++i)
    {
        if(sp[i] == size)
            result.push_back(i); // return vector with the beginning of the matches
    }
    return result;
}
void removeZeros(std::string& text)
{
    bool flag = false;// flag is 1 if in current word no more leading zeros
    for(size_t i = 0; i < text.size(); ++i)
    {
        if(text[i] == '0' && !flag)
        {
            if(text[i + 1] == '\n' || text[i + 1] == ' ')
                continue;
            else
                text[i] = ' ';
        }
        if(text[i] >= '1' || text[i] <= '9')
            flag = true;
        if(text[i] == '\n' || text[i] == ' ')
            flag = false;
    }
}
int main()
{
    std::string text;
    std::string str;
    std::string pattern;
    int ch;
    unsigned long val;
    while(std::cin>>val) // getting pattern
    {
        pattern += std::to_string(val);
        ch = std::cin.get();
        if(ch == '\n')
            break;
        if(ch == ' ' || ch == '\t')
        {
            pattern += " ";
            while(ch == ' ' || ch == '\t')
                ch = std::cin.get();
            if(ch == '\n')
                break;
            else
                std::cin.unget();
        }
        else
            std::cin.unget();
    }
    if(pattern.size() == 0)
        return 0;

    ch = std::cin.get();
    while(ch == '\n' || ch == '\t' || ch == ' ')// if \n follow before numbers
    {
        if(ch == '\n')
            text += "\n";
        ch = std::cin.get();
    }
    std::cin.unget();
    //now we are ready to get numbers
    while(std::cin>>val) // getting text
    {
        text += std::to_string(val) + " ";
        ch = std::cin.get();
        while(ch == '\n' || ch == '\t' || ch == ' ')
        {
            if(ch == '\n')
                text += "\n";
            /*if(ch == ' ' && isSpace)
            {
                text += ' ';
                isSpace = false;
            }*/
            ch = std::cin.get();
        }
        if(ch == '\0')
            break;
        else
            std::cin.unget();
    }
    if(text.size() == 0)
            return 0;
    text.pop_back();// We don't need last \n in this string
    text.pop_back();// We don't need space after last word
    // std::cout<<pattern<<" "<<pattern.size()<<std::endl;
    //std::cout<<text<<" "<<text.size()<<std::endl;
    
    size_t size = pattern.size();

    std::vector<word> wordsMap = Words(text);// getting vector with begining of all words in the text
    
    // for(int i = 0; i < wordsMap.size(); ++i)
    //      std::cout<<wordsMap[i].begin<<std::endl;
    //
    text = pattern + "@" + text;// concatenate pattern, text and separation symbol for prefix function

    std::cout<<"====================================\n";
    std::cout<<text<<std::endl;
    std::cout<<"====================================\n";    
    std::vector<size_t> result = KMP(text, size);// getting vector with prefix function result
    // std::cout<<result.size()<<std::endl;
    // for(int i = 0; i < result.size(); ++i)
    //     std::cout<<result[i]<<std::endl;
    for(size_t i = 0; i < result.size(); ++i)
    {
        for(size_t j = 0; j < wordsMap.size(); ++j)
        {
            if(result[i] - 2 * size == wordsMap[j].begin)
            {
                std::cout<<wordsMap[j].line<<", "<<wordsMap[j].n<<'\n';
                break;
            }
        }
    }
    return 0;
}
