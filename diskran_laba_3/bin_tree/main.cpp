#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
int main()
{
    BTree tree;
    tree.Remove(23);
    tree.Find(23);
    tree.Insert(1);
    tree.Insert(234);
    TNode* tmp = tree.Find(234);
    if(tmp != nullptr)
        std::cout<<tmp->GetVal()<<std::endl;
    tree.Remove(1);
    tree.Remove(234);
    tree.Remove(0);
    std::cout<<"OK\n";
    return 0;
}
