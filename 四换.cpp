#include <stdlib.h>
#include <stdio.h>
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 50 //线性表储存空间的初始分配量
#define LISTINCERMENT 10 //线性表的储存空间的分配增量
typedef char ElemType; //将一个char类型数据重新定义为ElemType
typedef struct
{
ElemType *elem; // 存储空间基址
int length; // 线性表当前长度
int listsize; // 当前分配的存储容量 
} SqList; // 俗称 顺序表
typedef int Status;
Status InitList_Sq(SqList &S) //// 构造一个空的线性表S。
{
S.elem =(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if (!S.elem) exit(OVERFLOW); // 存储分配失败
S.length = 0; // 空表长度为0
S.listsize = LIST_INIT_SIZE; // 初始存储容量
return OK;
} // InitList_Sq
Status ListInput(SqList &S,int n)
{
char *p=S.elem;
for(int i=1;i<=n;i++)
{ 
char ch=getchar();
*p=ch;
p++;
}
S.length=n;
return OK;
}
Status ListInsert_Sq(SqList &S,int i,ElemType X) //在线性表S中第i个位置之前插入新数据元素X，S的长度加1
{
if(i<1||i>S.length +1)return ERROR;//i值不合法
if(S.length >=S.listsize ) //当前储存空间已满，增加分配
{
ElemType * newbase=(ElemType *)realloc(S.elem,(S.listsize +LISTINCERMENT)*sizeof(ElemType));
if(!newbase)exit(OVERFLOW); //储存分配失败
S.listsize=S.listsize+LISTINCERMENT; //增加储存容量
S.elem=newbase; // 新基址
}
ElemType *q=&S.elem[i-1]; //q为插入位置
for(ElemType * p=&S.elem[S.length] ;p>=q;p--) *(p+1)=*p; //插入位置后元素后移
*q=X; //插入e
S.length++;//表长增1
return OK;
}// ListInsert_Sq
int main()
{
SqList S;
InitList_Sq(S);
ElemType X;
ListInput(S,5);
printf("%c",ListInsert_Sq(S,4,'U'));
printf("%s",S);
}
