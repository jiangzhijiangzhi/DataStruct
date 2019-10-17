#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 50//线性表存储空间初始分配量
#define LISTINCERMENT 10//线性表的储存空间的分配增量
typedef struct List{
	int *arry;
	int length;
	int listsize;
} SqList;
typedef int Status;
Status InitList(SqList &S)
{
	S.arry = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!S.arry)
		exit(OVERFLOW);
	S.length = 0;
	S.listsize = LIST_INIT_SIZE;
	return OK;
}//构造一个空的线性表

void ExpandList(SqList &L)
{
	L.listsize += LISTINCERMENT;
}//扩充表的当前容量

void ListInput(SqList &L)
{
	int i, length;
	int flow_control;
	int temp = 0;
	printf("请问您需要输入多少个数据!\n");
	scanf("%d", &length);
	if(length>L.listsize)
	{
	printf("超出表的容量!\n需要扩充吗?\n需要请按1\n不需要请按0\n");
	scanf("%d", &flow_control);
		while (0)
		{
		switch (flow_control)
			{
			case 0:exit(ERROR); break;
			case 1:ExpandList(L); break;
			default:printf("数据输入错误!\n"); break;
			}
		}
	}
 	else
	{
		for (i=0;i<length;i++)
		{
			printf("请输入第%d个数据\n", i + 1);
			scanf("%d", &L.arry[i]);
			++L.length;
			--L.listsize;
		}
	}
}//向线性表输入数据

int ListSort(SqList &L)
{
	 int i,j=0,t;
	 for(i=0;i<L.length;i++){
 		if(L.arry[i]<0){
 			t=L.arry[j];
		 	L.arry[j]=L.arry[i];
		 	L.arry[i]=t;
		 	j++;
		 }
 	}
	return OK;
}//对线性表数据按照正负排序 

 void ListOutput(SqList &L,int length){
	for(int i=0;i<L.length;i++)printf("%d",L.arry[i]);
}//输出线性表内容

int main(){
	SqList L;
	InitList(L);
	ListInput(L);
	ListSort(L);
	ListOutput(L,L.length);
	printf("\n");
}
