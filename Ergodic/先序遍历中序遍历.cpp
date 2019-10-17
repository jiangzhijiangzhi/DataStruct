#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef struct BiTNode
{
    char data;
    BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
BiTree T,p,q;
string spre,smid;
void findChild(int a,int c,int len,BiTree &T)
{
    T=(BiTree)malloc(sizeof(BiTNode));
    T->data=spre[a];
    if (len==1) {
        T->lchild=NULL;
        T->rchild=NULL;
        return ;
    }
    int m=c;
    while (smid[m]!=spre[a]) m++;
    if (m==c) {
        T->lchild=NULL;
    }
    else {
        findChild(a+1,c,m-c,T->lchild);
    }
    if (m>=len+c-1) { 
        T->rchild=NULL;
    }
    else {
        findChild(a+1+m-c,m+1,len-m+c-1,T->rchild);
    }
}
Status PostOrderTraversal(BiTree T)
{
    if (T!=NULL) {
        PostOrderTraversal(T->lchild);
        PostOrderTraversal(T->rchild);
        printf("%c",T->data);
    }
    return OK;
}
int main()
{
    cin>>spre>>smid;
    findChild(0,0,spre.size(),T);
    PostOrderTraversal(T);
	return 0;
}
