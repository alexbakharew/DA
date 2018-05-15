#ifndef TNODE
#define TNODE
typedef struct TNode TNode;
struct TNode
{
    TNode* Left;
    TNode* Right;
    TNode* Parent;
    char* Key;
    unsigned long long int Number;
    short Balance;
};

#endif // TNODE

