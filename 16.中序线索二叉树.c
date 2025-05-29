#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int ltag;
    int rtag;
} TreeNode;

void createTree(TreeNode **T, char *data, int *index)
{
    char ch = data[*index];
    *index += 1;
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        createTree(&(*T)->lchild, data, index);
        createTree(&(*T)->rchild, data, index);
    }
}

void inThreadTree(TreeNode *T, TreeNode **pre)
{
    if (T)
    {
        inThreadTree(T->lchild, pre);
        if (T->lchild == NULL)
        {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
        inThreadTree(T->rchild, pre);
    }
}
TreeNode *getFirst(TreeNode *T)
{
    while (T->rtag == 0)
        T = T->lchild;

    return T;
}

TreeNode* getNext(TreeNode* node){
    if(node->rtag==1){
        return node->rchild;
    }else{
        return getFirst(node->rchild);
    }
}

int main(int argc, char *argv[])
{
    TreeNode *T;
    TreeNode *pre = NULL;
    int index = 0;
    createTree(&T, argv[1], &index);
    inThreadTree(T, &pre);
    pre->rtag = 1;
    pre->rchild = NULL;
    for(TreeNode* node=getFirst(T);node!=NULL;node=getNext(node)){
        printf("%c ",node->data);
    }
    printf("\n");
    preOrder(T);
    return 0;
}