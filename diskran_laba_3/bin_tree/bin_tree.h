#ifndef BIN_TREE_H
#define BIN_TREE_H
#include <cstdlib>
class TNode
{
public:
    TNode();
    ~TNode();
    long GetVal();
    void SetVal(long val);
 private:
     TNode* Left;
     TNode* Right;
     long Value;

friend class TBtree;
};

class TBtree
{
public:
    TBtree();
    ~TBtree();
    bool Insert(long value);
    bool Remove(long value);
    TNode* Find(long value);
    size_t GetSize();
private:
    void ClearTree(TNode*& nd);
    bool Insert_(TNode*& nd, long val);
    bool Remove_(TNode*& nd, long val);
    TNode* Find_(TNode*& nd, long val);
    TNode* Root;
    size_t Size;
};
#endif
