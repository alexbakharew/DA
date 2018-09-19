#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
int main()
{
    TBtree tree;
    long val;

    for(int i = 0; i < 1000000; ++i)
    {
        std::cin>>val;
        tree.Insert(val);
    }
    std::cout<<"OK\n";
    for(int i = 0; i < 1000000; ++i)
    {
        std::cin>>val;
        tree.Find(val);
    } 
    std::cout<<"OK\n";    
    return 0;
}
