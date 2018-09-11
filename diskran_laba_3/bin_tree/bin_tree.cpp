#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
TNode::TNode()
{
    Left = Right = nullptr;
}
TNode::~TNode()
{
    if(Left != nullptr)
        delete Left;
    if(Right != nullptr)
        delete Right;
}
long TNode::GetVal()
{
    return Value;
}
BTree::BTree()
{
    Root = nullptr;
}
void BTree::ClearTree(TNode* nd)
{
    if(nd == nullptr)
        return;
    if(nd->Left != nullptr)
        ClearTree(nd->Left);
    if(nd->Right != nullptr)
        ClearTree(nd->Right);
    delete nd;
    nd = nullptr;
    return;
}

BTree::~BTree()
{
    ClearTree(Root);
}
bool BTree::Insert(long val)
{
    TNode* nd = Root;
    while(nd != nullptr)
    {
        if(nd->Value > val)
            nd = nd->Left;
        else if(nd->Value < val)
            nd = nd->Right;
        else
            return false; // item already added
    }
    nd = new TNode;
    if(nd == nullptr)
        return false; // Not enough memory
    nd->Left = nd->Right = nullptr;
    nd->Value = val;
    if(Root == nullptr)
        Root = nd;
    return true;
}
bool BTree::Remove(long val)
{
    TNode* nd = Root;
    if(nd == nullptr)
        return false;
    while(nd != nullptr)
    {
        if(nd->Value > val)
            nd = nd->Left;
        else if(nd->Value < val)
            nd = nd->Right;
        else
        {
            delete nd;
            nd = nullptr;
            return true;
        }
    }
    return false;
}
TNode* BTree::Find(long val)
{
    TNode* nd = Root;
    while(nd != nullptr)
    {
        if(nd->Value > val)
            nd = nd->Left;
        else if(nd->Value < val)
            nd = nd->Right;
        else
            return nd;
    }
    return nullptr;
}
