#include <iostream>
#include <string>
#include <vector>

struct word
{
    size_t begin;
    size_t n;
    size_t line;
};

std::vector<word> Words(const std::string& s)
{
    std::vector<word> wordsMap;

    //word init;
    //wordsMap.push_back(init);// first and may be only one word in whole string
    // wordsMap[0].begin = 0;
    // wordsMap[0].line = 1;
    // wordsMap[0].n = 1;

    size_t line = 1;
    size_t n = 1;
    //bool isWord = false;
    for(size_t i = 0; i < s.size(); ++i)
    {
        if(i == 0 && s[i] == '\n' && s[i + 1] != '\n')
        {
            ++line;
            word tmp = {i + 1, n, line};
            wordsMap.push_back(tmp);
            ++n;
        }
        else if(i == 0)
        {
            word tmp = {i, n, line};
            wordsMap.push_back(tmp);
            ++n;
        }
        else if(s[i] == '\n' && s[i + 1] == '\n')
        {
            ++line;
            n = 1;
        }
        else if(s[i] == '\n' && s[i + 1] != '\n')
        {
            if(s[i + 1] == EOF || s[i + 1] == '\0')
                    break;
            ++line;
            n = 1;
            word tmp = {i + 1, n, line};
            wordsMap.push_back(tmp);
            ++n;
        }
        else if(s[i] == ' ' && s[i + 1] != ' ' && s[i + 1] != '\n')
        {
            word tmp = {i + 1, n, line};
            wordsMap.push_back(tmp);
            ++n;
        }
    }
    return wordsMap;
}

std::vector<size_t> prefix_function (std::string& s)
{
    size_t n =  s.length();
    std::vector<size_t> pi(n);
    for (size_t i = 1; i < n; ++i)
    {
        if(s[i] == '\t')
            s[i] = ' ';
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

int main(int argc, char const *argv[])
{
    std::string pattern;
    std::string text;
    unsigned long int val;
    int ch;
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
    if(pattern.back() == ' ' || pattern.back() == '\n')
        pattern.pop_back();

//----------------------------------------------------------------------------------
   // int line = 1;
   // int n = 1;
    ///int i = 0;
    //word wordsMap;
    ch = std::cin.get();
    while(ch == '\n' || ch == '\t' || ch == ' ')// if \n follow before numbers
    {
        if(ch == '\n')
            //++line;
            text += "\n";
        //++i;
        ch = std::cin.get();
    }
    std::cin.unget();
    //now we are ready to get numbers
    while(std::cin>>val) // getting text
    {
        std::string tmp = std::to_string(val);
        
       // i += tmp.size() - 1;

        text += tmp + " ";
        ch = std::cin.get();
        while(ch == '\n' || ch == '\t' || ch == ' ')
        {
            if(ch == '\n')
            {
                int k = text.size();
                if(text[k - 1] == ' ')
                    text[k - 1] = '\n';
                else    
                text += "\n";
            }
            
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
    //text.pop_back();// We don't need space after last word
    // Input is ready

    std::vector<word> wordsMap = Words(text); // map of words
    
    //std::cout<<"Now we have "<<wordsMap.size()<<" words\n";
    
    text = pattern + "@" + text;// concatenate pattern, text and separation symbol for prefix function

    size_t size = pattern.size(); // necessery for KMP algo

    std::vector<size_t> result = KMP(text, size);
    //std::cout<<"There are "<<result.size()<<"matches\n";
    for(size_t i = 0; i < result.size(); ++i)
    {
        for(size_t j = 0; j < wordsMap.size(); ++j)
        {
            if(result[i] - 2 * size == wordsMap[j].begin)
            {
                std::cout<<wordsMap[j].line<<", "<<wordsMap[j].n<<"\n";
                break;
            }
        }
    }
    return 0;
}
