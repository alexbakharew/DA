#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
TNode::TNode()
{
    Left = Right = nullptr;
}
TNode::~TNode(){}
void TNode::SetVal(long val)
{
    Value = val;
}
long TNode::GetVal()
{
    return Value;
}
TBtree::TBtree()
{
    Root = nullptr;
    Size = 0;
}
TBtree::~TBtree()
{
    //std::cout<<Size<<std::endl;
    ClearTree(Root);
    //std::cout<<Size<<std::endl;
}
size_t TBtree::GetSize()
{
    return Size;
}
void TBtree::ClearTree(TNode*& nd)
{
    if(nd == nullptr)
        return;
    ClearTree(nd->Left);
    ClearTree(nd->Right);
    delete nd;
    nd = nullptr;
    --Size;
    return;
}
bool TBtree::Insert(long val)
{
    return Insert_(Root, val);
}
TNode* TBtree::Find(long val)
{
    return Find_(Root, val);
}
TNode* TBtree::Find_(TNode*& nd, long val)
{
    if(nd == nullptr)
        return nullptr;
    if(nd->Value > val)
        Find_(nd->Left, val);
    else if(nd->Value < val)
        Find_(nd->Right, val);
    else return nd;
}
bool TBtree::Insert_(TNode*& nd, long val)
{
    if(nd == nullptr)
    {
        nd = new TNode;
        if(nd == nullptr)
            return false; // Not enough memory
        nd->Value = val;
        ++Size;
        return true;
    }
    else if(nd->Value > val)
        Insert_(nd->Left, val);
    else if(nd->Value < val)
        Insert_(nd->Right, val);
    else return false; // item already added
}

