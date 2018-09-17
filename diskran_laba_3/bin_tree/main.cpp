#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
int main()
{
    TBtree tree;
    long val;
    FILE* fd = fopen("01.t", "r");

    for(int i = 0; i < 10000000; ++i)
    {
        std::
        std::cin>>val;
        tree.Insert(val);
    }
    std::cout<<"OK\n";
    for(int i = 0; i < 10000000; ++i)
    {
        std::cin>>val;
        tree.Find(val);
    } 
    std::cout<<"OK\n";    
    return 0;
}
