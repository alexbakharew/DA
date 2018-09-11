#ifndef BIN_TREE_H
#define BIN_TREE_H
class TNode
{
public:
    TNode();
    ~TNode();
    long GetVal();
 private:
     TNode* Left;
     TNode* Right;
     long Value;

friend class BTree;
};
#endif
class BTree
{
public:
    BTree();
    ~BTree();
    bool Insert(long value);
    bool Remove(long value);
//    bool Remove(TNode* nd);
    TNode* Find(long value);
private:
    void ClearTree(TNode* nd);
    TNode* Root;
};
