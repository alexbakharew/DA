#include <iostream>
#include <cstdlib>
#include <string>
#include <map>
void ToLowerCase(std::string& str)
{
    for(size_t i = 0; i != str.size(); ++i)
    {
        if(str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] += 32;
        }
    }
}

int main()
{
    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    std::map<std::string, unsigned long long int> lib;
    char command;
    std::string str;
    unsigned long long int val;
    std::cin.get(command);
    while(!std::cin.eof())
    {
        if(command == '+') // + akiufh 34
        {
            std::cin.get();// skip space
            std::cin>>str;
            ToLowerCase(str);
            std::cin.get();// skip space
            std::cin>>val;
            std::cin.get();// skip space
            auto it = lib.find(str);
            if((*it).first != str)// elem is not in lib
            {
                lib.insert(std::pair<std::string, unsigned long long int>(str, val));            
                std::cout<<"OK\n";
            }
            else
            {
                std::cout<<"Exist\n";
            }
        }
        else if(command == '-') // - a
        {
            std::cin.get();// skip space
            std::cin>>str;
            ToLowerCase(str);            
            std::cin.get();// skip space            
            auto it = lib.find(str);
            if((*it).first == str) //elem finded
            {
                lib.erase(it);
                std::cout<<"OK\n";
            }
            else
            {
                std::cout<<"NoSuchWord\n";
            }
        }
        else
        {
            std::cin.unget();
            std::cin>>str;
            ToLowerCase(str);
            //std::cout<<str;            
            std::cin.get();// skip space
            auto it = lib.find(str);
            if((*it).first == str)
            {
                std::cout<<"OK: "<<(*it).second<<"\n";
            }
            else
            {
                std::cout<<"NoSuchWord\n";
            }
        }
        std::cin.get(command);
        
    } 
    return 0;
}