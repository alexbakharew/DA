#include <iostream>
#include <string>
#include <vector>
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
    unsigned long int val;
    int ch;
    //--------------------------------------
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
    //---------------------------------------
    
	std::string raw_text;
    std::string text;
    
    size_t line = 1; // we need to count lines before main text
    
    ch = std::cin.get();
    while(ch == ' ' || ch == '\n')
    {
        if(ch == '\n')
            ++line;
        ch = std::cin.get();
    }
    if(ch == '\0' || ch == EOF)
        return 0;
    if(ch >= '0' && ch <= '9')
        std::cin.unget(), ch = 0;
    // ready to get text
   while(std::cin>>val)  
   {
        std::string tmpStr = std::to_string(val);
        text += tmpStr + " ";
        raw_text += tmpStr;
        ch = std::cin.get();

        while(ch == ' ' || ch == '\n')
        {
            if(ch == '\n')
                raw_text += "\n";
            ch = std::cin.get();
        }
        std::cin.unget();
        if(raw_text.back() != '\n')
            raw_text += " ";
    
    }
    raw_text.pop_back();
    raw_text += '\0';
    text.pop_back();
    //---------------------------------------
    if(text.size() < pattern.size())
        return 0;
    text = pattern + "@" + text;// concatenate pattern, text and separation symbol for prefix function

    size_t size = pattern.size(); // necessery for KMP algo

    std::vector<size_t> result = KMP(text, size);
    if(result.size() == 0)
        return 0;
 	// std::cout<<"-----------------\n";
// 	std::cout<<"I find "<<result.size()<<" matches"<<std::endl;
// //	std::cout<<result[1] - size<<std::endl;
 	// std::cout<<"raw_text ="<<raw_text<<"|||\n";
 	// std::cout<<"text ="<<text<<"|||\n";
// 	std::cout<<"-----------------\n";
    size_t n = 1;
    size_t j = 0; // Iter for result vector
    int shift = 0;// Amount of useless \n in raw_text
    for(int i = 0; i < raw_text.size(); i++)
    {
        if(raw_text[i] == '\n')
        {
            if(raw_text[i - 1] == '\n')
                ++shift;
            ++line;
            n = 1;
        }
        else if(raw_text[i] == ' ') 
        {
            ++n;
            
        }
        
        if(result[j] - 2*size + shift == i)
        {
            std::cout<<line<<", "<<n<<"\n";
            ++j;
        }
    }
    return 0;
}
