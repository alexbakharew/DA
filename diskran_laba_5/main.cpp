#include <iostream>
#include "suffix_tree.h"
int main() 
{
    char terminal = '$';
    std::vector<char> alphabet('z' - 'a' + 1);
    for (std::size_t i = 'a'; i <= 'z'; ++i) 
        alphabet[i - 'a'] = i;
    TSuffixTree tree(alphabet, terminal);
    //std::ios::sync_with_stdio(false);
    std::string text;
    std::cin >> text;
    for (std::size_t i = 0, end = text.size(); i < end; ++i)
        tree.PushBack(text[i]);
    tree.PushBack(terminal);
    TSuffixArray array(tree);
    unsigned long long counter = 0;
    while (std::cin >> text)
    {
        counter++;
        std::vector<std::size_t> result = array.Find(text);
        if (!result.empty())
        {
            printf("%llu: ", counter);
            for (std::size_t i = 0; i < result.size(); ++i)
            {
                printf("%lu", result[i] + 1);
                if (i < result.size() - 1)
                    printf(", ");
            }
            std::cout << "\n";
        }
    }
    return 0;
}