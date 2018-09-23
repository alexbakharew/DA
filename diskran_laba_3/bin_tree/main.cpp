#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
#include <random>
int main()
{
    TBtree tree;
    long val;
    // std::random_device rd;  //Will be used to obtain a seed for the random number engine
    // std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    // std::uniform_int_distribution<> dis(-5000, 5000);
    for(int i = 0; i < 2000; ++i)
    {
        std::cin>>val;
        tree.Insert(val);
    }
    // for(int i = 0; i < 10; ++i)
    // {
    //     std::cin>>val;
    //     tree.Find(val);
    // }
    return 0;
}
