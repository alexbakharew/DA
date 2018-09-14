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

class BTree
{
public:
    BTree();
    ~BTree();
    bool Insert(long value);
    bool Remove(long value);
    TNode* Find(long value);
private:
    void ClearTree(TNode*& nd);
    bool _insert(TNode*& nd, long val);
    bool _remove(TNode*& nd, long val);
    TNode* _find(TNode*& nd, long val);
    TNode* Root;
};
#endif
