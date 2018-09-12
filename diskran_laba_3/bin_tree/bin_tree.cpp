#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
TNode::TNode()
{
    Left = Right = nullptr;
}
TNode::~TNode()
{
//    if(Left != nullptr)
//        delete Left;
//    if(Right != nullptr)
//        delete Right;
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
    if(_insert(&Root, val))
        return true;
    else return false;
}
TNode* BTree::Find(long val)
{
    return _find(&Root, val);
}
TNode* BTree::_find(TNode** nd, long val)
{
    if((*nd) == nullptr)
        return nullptr;
    if((*nd)->Value > val)
        _find(&((*nd)->Left), val);
    else if((*nd)->Value < val)
        _find(&((*nd)->Right), val);
    else return *nd;
}
bool BTree::_insert(TNode** nd, long val)
{
    if((*nd) == nullptr)
    {
        (*nd)  = new TNode;
        if((*nd)  == nullptr)
            return false; // Not enough memory
        (*nd)->Left = (*nd)->Right = nullptr;
        (*nd)->Value = val;
        return true;
    }
    else if((*nd)->Value > val)
        _insert(&((*nd)->Left), val);

    else if((*nd)->Value < val)
        _insert(&((*nd)->Right), val);
    else return false; // item already added
}
bool BTree::Remove(long val)
{

}

