#include <iostream>
#include <string.h>
#include "node.h"
#include "avl_tree.h"
#include <stdbool.h>
#ifndef max
    #define max(a,b) ((a) > (b) ? (a) : (b))
#endif

TAvlTree::TAvlTree()
{
    Root = NULL;
}
TAvlTree::~TAvlTree()
{
    SimpleDelete(Root);
}
void TAvlTree::SimpleDelete(TNode* n)
{
    if(n == NULL) return;
    SimpleDelete(n->Left);
    SimpleDelete(n->Right);
    delete[] n->Key;
    delete n;
    n = NULL;
}

TNode** TAvlTree::GetRoot()
{
    return &Root;
}
void TAvlTree::UpdateRoot()
{
    while(Root->Parent != NULL)
    {
        Root = Root->Parent;
    }
}

int TAvlTree::Height(TNode* node)
{
    if (node == NULL) return 0;
    int left = Height(node->Left);
    int right = Height(node->Right);
    return max(left, right) + 1;
}
int TAvlTree::CountBalance(TNode* node)
{
    if(node == NULL) return 0;
    return Height(node->Left) - Height(node->Right);
}
void TAvlTree::SimpleLeftRotate(TNode* pivot)
{
    TNode* tmp = pivot->Right->Left;
    TNode* parentOfPivot = pivot->Parent;

    if(parentOfPivot != NULL)
    {
        if(parentOfPivot->Left == pivot) parentOfPivot->Left = pivot->Right;
        else parentOfPivot->Right = pivot->Right;
    }
    pivot->Parent = pivot->Right;
    if(tmp != NULL) tmp->Parent = pivot;
    pivot->Right->Parent = parentOfPivot;

    pivot->Right->Left = pivot;
    pivot->Right = tmp;
    UpdateRoot();
}

void TAvlTree::SimpleRightRotate(TNode* pivot)
{
    TNode* tmp = pivot->Left->Right;
    TNode* parentOfPivot = pivot->Parent;

    if(parentOfPivot != NULL)
    {
        if(parentOfPivot->Right == pivot) parentOfPivot->Right = pivot->Left;
        else parentOfPivot->Left = pivot->Left;
    }
    pivot->Parent = pivot->Left;
    if(tmp != NULL) tmp->Parent = pivot;
    pivot->Left->Parent = parentOfPivot;

    pivot->Left->Right = pivot;
    pivot->Left = tmp;
    UpdateRoot();
}

void TAvlTree::LeftRotation(TNode* current)
{
    // according to balance table
    SimpleLeftRotate(current);
    if(current->Parent->Balance == 0)
    {
        current->Parent->Balance = 1;
        current->Balance = -1;
    }
    else
    {
        current->Parent->Balance = 0;
        current->Balance = 0;
    }

}
void TAvlTree::RightRotation(TNode* current)
{
    // according to balance table
    SimpleRightRotate(current);
    if(current->Parent->Balance == 0)
    {
        current->Parent->Balance = -1;
        current->Balance = 1;
    }
    else
    {
        current->Parent->Balance = 0;
        current->Balance = 0;
    }
}
void TAvlTree::BigLeftRotation(TNode* current)
{
    // according to balance table
    SimpleRightRotate(current->Right);
    SimpleLeftRotate(current);
    if(current->Parent->Balance == 1)
    {
        current->Balance = 0;
        current->Parent->Right->Balance = -1;
    }
    else if(current->Parent->Balance == -1)
    {
        current->Balance = 1;
        current->Parent->Right->Balance = 0;
    }
    else
    {
        current->Balance = 0;
        current->Parent->Right->Balance = 0;
    }
    current->Parent->Balance = 0;
}
void TAvlTree::BigRightRotation(TNode* current)
{
    // according to balance table
    SimpleLeftRotate(current->Left);
    SimpleRightRotate(current);
    if(current->Parent->Balance == 1)
    {
        current->Balance = -1;
        current->Parent->Left->Balance = 0;
    }
    else if(current->Parent->Balance == -1)
    {
        current->Balance = 0;
        current->Parent->Left->Balance = 1;
    }
    else
    {
        current->Balance = 0;
        current->Parent->Left->Balance = 0;
    }
    current->Parent->Balance = 0;
}

void TAvlTree::RecountBalanceInsert(TNode* node, bool src)
{
    if(node == NULL) return;
    if(!src)// left
    {
        node->Balance++;
    }
    else
    {
        node->Balance--;
    }
    if(node->Balance == 0) return;
    if(node->Balance > 1)//==2
    {
        int L = Height(node->Left->Left);
        int R = Height(node->Left->Right);
        if(R > L)
        {
            BigRightRotation(node);
        }
        else
        {
            RightRotation(node);
        }
        node = node->Parent;
    }
    else if(node->Balance < -1)//==-2
    {
        //int L, R;
        int L = Height(node->Right->Left);
        int R = Height(node->Right->Right);
        if(L > R)
        {
            BigLeftRotation(node);
        }
        else
        {
            LeftRotation(node);
        }
        node = node->Parent;
    }
    if(node->Parent == NULL)return;
    if(node->Balance == 0) return;
    if(node->Parent->Left == node) return RecountBalanceInsert(node->Parent, false);
    else return RecountBalanceInsert(node->Parent, true);
}
void TAvlTree::RecountBalanceDelete(TNode* node, bool src)
{
    if(node == NULL) return;
    if(!src) // from left
    {
        node->Balance--;
    }
    else //from right
    {
        node->Balance++;
    }
    if(node->Balance == 1 || node->Balance == -1) return;
    if(node->Balance > 1) //==2
    {
        int L = Height(node->Left->Left);
        int R = Height(node->Left->Right);
        if(R > L)
        {
            BigRightRotation(node);
        }
        else
        {
            RightRotation(node);
        }
        node = node->Parent;
    }
    else if(node->Balance < -1)//==-2
    {
        int L = Height(node->Right->Left);
        int R = Height(node->Right->Right);
        if(L > R)
        {
            BigLeftRotation(node);
        }
        else
        {
            LeftRotation(node);
        }
        node = node->Parent;
    }
    if(node == NULL) return;
    if(node->Balance == 1 || node->Balance == -1) return;
    if(node->Parent == NULL) return;
    if(node->Parent->Left == node) return RecountBalanceDelete(node->Parent, false);
    else return RecountBalanceDelete(node->Parent, true);
}
bool TAvlTree::Search(char* str,  TNode** node, size_t len)
{
    if((*node) == NULL)
    {
        printf("NoSuchWord\n");
        return false;
    }
    int res = strncmp((*node)->Key, str,len + 1);
    if(res == 0)
    {
        printf("OK: %llu\n",(*node)->Number);
        return true;
    }
    else if(res < 0)
    {
        return Search(str, &((*node)->Left), len);
    }
    else if(res > 0)
    {
        return Search(str, &((*node)->Right), len);
    }
    return false;
}
bool TAvlTree::Insert(unsigned long long int number, char* str, TNode** node, TNode** parent, size_t len)
{
    if(*node == NULL)
    {
        TNode* tmp = new TNode;
        tmp->Left = NULL;
        tmp->Right = NULL;
        if(parent == NULL) tmp->Parent = NULL;
        else tmp->Parent = *parent;
        tmp->Number = number;

        tmp->Key = new char[len + 1];
        strncpy(tmp->Key, str, len);
        tmp->Key[len] = '\0';   

        tmp->Balance = 0;
        *node = tmp;
        if(tmp->Parent != NULL)
        {
            if(tmp->Parent->Left == tmp) RecountBalanceInsert((*node)->Parent, false);
            else RecountBalanceInsert((*node)->Parent, true);
        }
        printf("OK\n");
        return true;
    }
    int res = strncmp((*node)->Key, str, len + 1);
    if(res == 0)
    {
        printf("Exist\n");
        return false;
    }
    else if(res < 0)
    {
        return Insert(number, str, &((*node)->Left), node, len);
    }
    else if(res > 0)
    {
       return Insert(number, str, &((*node)->Right), node, len);
    }
    else return false;
}
bool TAvlTree::Remove(char* str, TNode** node, size_t len)
{
    if((*node) == NULL) return false;
    int res = strncmp((*node)->Key, str,len + 1);
    if(res == 0) // we find suitable node
    {
        TNode* tmp = *node;
        TNode* parentOfNode = (*node)->Parent;

        if((*node)->Left == NULL && (*node)->Right == NULL)
        {
            bool src;
            if((*node)->Parent == NULL) src = false;
            else if((*node)->Parent->Left == (*node)) src = false;
            else src = true;

            *node = NULL;
            delete[] tmp->Key;
            tmp->Key = NULL;            
            delete tmp;
            tmp = NULL;
            RecountBalanceDelete(parentOfNode, src);
            return true;
        }
        else if((*node)->Right != NULL && (*node)->Left == NULL)
        {
            bool src;
            if((*node)->Parent == NULL) src = false;
            else if((*node)->Parent->Left == (*node)) src = false;
            else src = true;

            (*node) = (*node)->Right;
            (*node)->Parent = tmp->Parent;
            delete[] tmp->Key;
            tmp->Key = NULL;
            delete tmp;
            tmp = NULL;
            RecountBalanceDelete(parentOfNode, src);
            return true;
        }
        else if((*node)->Left != NULL && (*node)->Right == NULL)
        {
            bool src;
            if((*node)->Parent == NULL) src = false;
            else if((*node)->Parent->Left == (*node)) src = false;
            else src = true;

            (*node) = (*node)->Left;
            (*node)->Parent = tmp->Parent;
            delete[] tmp->Key;
            tmp->Key = NULL;            
            delete tmp;
            tmp = NULL;
            RecountBalanceDelete(parentOfNode, src);
            return true;
        }
        else
        {
            *node = (*node)->Right;
            TNode* tmp2 = *node;
            if((*node)->Left == NULL)
            {
                bool src;
                if(tmp->Left == (*node)) src = false;
                else src = true;

                (*node)->Parent = parentOfNode;
                (*node)->Balance = tmp->Balance;
                if(tmp->Left != NULL) tmp->Left->Parent = *node;
                (*node)->Left = tmp->Left;
                if(parentOfNode != NULL)
                {
                    if(parentOfNode->Left == *node) parentOfNode->Left = *node;
                    else parentOfNode->Right = *node;
                }
                delete[] tmp->Key;
                tmp->Key = NULL;                
                delete tmp;
                tmp = NULL;
                RecountBalanceDelete(tmp2, src);
            }
            else //dive in Left branch untill NULL
            {
                while((*node)->Left != NULL)
                {
                    (*node) = (*node)->Left;
                }

                parentOfNode = (*node)->Parent;
                TNode* tmp2 = (*node)->Right;
                if(tmp2 != NULL)
                {
                    tmp2->Parent = parentOfNode;
                }
                parentOfNode->Left = tmp2;
                (*node)->Parent = tmp->Parent;
                (*node)->Right = tmp->Right;
                (*node)->Left = tmp->Left;
                (*node)->Balance = tmp->Balance;
                tmp->Left->Parent = (*node);
                tmp->Right->Parent = (*node);
                if(tmp->Parent != NULL)
                {
                    if(tmp->Parent->Left == tmp) tmp->Parent->Left = *node;
                    else if(tmp->Parent->Right == tmp) tmp->Parent->Right = *node;
                }
                delete[] tmp->Key;
                tmp->Key = NULL;                
                delete tmp;
                tmp = NULL;
                RecountBalanceDelete(parentOfNode, false);
            }
            return true;
        }
    }
    else if(res < 0)
    {
        return Remove(str, &(*node)->Left, len);
    }
    else if(res > 0)
    {
        return Remove(str, &(*node)->Right, len);
    }
    return false;
}
void TAvlTree::LkpDelete(TNode **node)
{
}
void TAvlTree::LkpSave(TNode* node, FILE* file)
{
    if(node == NULL) return;
    char buff[257];
    strcpy(buff, node->Key);
    fwrite(node, sizeof(TNode), 1, file);
    fwrite(buff, sizeof(buff), 1, file);    
    LkpSave(node->Left, file);
    LkpSave(node->Right, file);
}
void TAvlTree::LkpLoad(TNode** node, TNode* Parent, FILE* file)
{
        TNode tmp;
        char tmpBuff[257];
        if(fread(&tmp, sizeof(TNode), 1,file) < 1) return;
        fread(tmpBuff, sizeof(tmpBuff), 1,file);
        *node = new TNode;
        
        **node = tmp;
        //if(*node == NULL) return;
        size_t size = strlen(tmpBuff);
        (*node)->Key = new char[size + 1];
        strncpy((*node)->Key, tmpBuff, size);
        (*node)->Key[size] = '\0';
        (*node)->Parent = Parent;
   
    if((*node)->Left != NULL) LkpLoad(&(*node)->Left,(*node), file);
    if((*node)->Right != NULL) LkpLoad(&(*node)->Right,(*node), file);
    else return;
}
void TAvlTree::CheckBalance(TNode** node)
{
    if((*node) == NULL) return;
    int bal = CountBalance((*node));
    if((*node)->Balance != bal)
    {
      std::cout<<"WRONG ANSWER!"<<" "<<bal<<" "<<(*node)->Key<<std::endl;
      return;
    }
    CheckBalance(&(*node)->Left);
    CheckBalance(&(*node)->Right);
}
void TAvlTree::print(TNode* node, int level)
{ // lkp
    if(node == NULL) return;
    print(node->Right, level + 1);
    for(int i = 0; i < level; ++i)
    {
        printf("   ");
    }
    printf("%s",node->Key);
    printf("=");
    printf("%d\n", node->Balance);
    print(node->Left, level + 1);
}

