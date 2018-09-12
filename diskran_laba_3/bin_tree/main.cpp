#include <iostream>
#include <cstdlib>
#include <random>
#include "bin_tree.h"
int main()
{
    BTree tree;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(-5000, 5000);
    for(int i = 0; i < 500; ++i)
    {
        tree.Insert(dis(gen));
    }
    for(int i = 0; i < 500; ++i)
    {
        tree.Find(dis(gen));
    }
    std::cout<<"OK"<<std::endl;
    return 0;
}
