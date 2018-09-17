#include <iostream>
#include <cstdlib>
#include "bin_tree.h"
TNode::TNode(){}
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
}
void TBtree::ClearTree(TNode*& nd)
{
    if(nd == nullptr)
        return;
    if(nd->Left != nullptr)
        ClearTree(nd->Left);
    else if(nd->Right != nullptr)
        ClearTree(nd->Right);
    delete nd;
    nd = nullptr;
    return;
}

TBtree::~TBtree()
{
    ClearTree(Root);
}
bool TBtree::Insert(long val)
{
    if(Insert_(Root, val))
        return true;
    else return false;
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
        nd->Left = nd->Right = nullptr;
        nd->Value = val;
        return true;
    }
    else if(nd->Value > val)
        return Insert_(nd->Left, val);
    else if(nd->Value < val)
        return Insert_(nd->Right, val);
    return false; // item already added
}

