#include "stdafx.h"
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
# include <stdio.h>
# include <stdlib.h>
/*---------------线性表动态分配顺序存储结构-----------------*/

# define LIST_INIT_SIZE 100 //线性表存储空间初始分配量    

# define LISTINCREMENT 10   //线性表存储空间增加量        
/*----------------------------------------------------------*/
/*---------------------函数返回结果-------------------------*/
#define OK 1

#define ERROR 0

#define TRUE 1

#define FALSE 0

#define OVERFLOW -2//内存溢出

#define INFEASIBLE -1
/*----------------------------------------------------------*/
/*-----------------------函数列表---------------------------

NewList()//创建一个新的线性表

EmptyList()//清空线性表

ListEmpty()//判断某个线性表是否为空表并返回结果

ListLength()//返回某个线性表中的元素个数

GetElem()//返回指定元素的值

ListInPut()//向线性表输入数据

TextOutPut()//输出相应的文字

ExpandList()//扩充线性表容量

ListOutPut()//输出线性表的内容

ListInsert()//向线性表中指定位置插入某个元素

int ListDelete()//删除线性表中指定元素并返回其值

------------------------------------------------------------*/
typedef struct List
{
	int * arry;//保存数组的首地址
	int len;//数组当前长度
	int listsize;//为数组分配的容量大小
}SqList;//结构体的新名称

int NewList(SqList *pLa)
{
	pLa->arry = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!pLa->arry)
		exit(OVERFLOW);
	pLa->len = 0;
	pLa->listsize = LIST_INIT_SIZE;
	return OK;
}//构造一个空的线性表

 

 

void ExpandList(SqList * ppLa)

{

	ppLa->listsize += LISTINCREMENT;

}//扩充表的当前容量

 

 

void ListOutPut(SqList *pLa, int len)

{

	int i;

 

 

	for (i = 0; i <= len - 1; i++)

		printf("%d\n", pLa->arry[i]);

}//输出线性表的内容

 

 

void ListInPut(SqList *pLa)

{

	int i, len;

	int flow_control;//流程控制

	int temp = 0;

 

 

	printf("请问您需要输入多少个数据!\n");

	scanf_s("%d", &len);

 

 

	if (len > pLa->listsize)

	{

		printf("超出表的容量!\n需要扩充吗?\n需要请按1\n不需要请按0\n");

		scanf_s("%d", &flow_control);

 

 

		while (0)

		{

			switch (flow_control)

			{

			case 0:exit(ERROR); break;

			case 1:ExpandList(pLa); break;

			default:printf("数据输入错误!\n"); break;

			}

		}

	}

 

 

	else

	{

		for (i = 0; i <= len - 1; i++)

		{

			printf("请输入第%d个数据\n", i + 1);

			scanf_s("%d", &pLa->arry[i]);

			++pLa->len;

			--pLa->listsize;

		}

	}

 

 

}//对线性表输入数据

 

 

int ListInsert(SqList *pLa, int place, int math)//place为插入的位置，math为插入的数值

{

	int * newsize, *q, *p;

 

 

	if (place < 1 || place > pLa->len + 1)

		return ERROR;

	if (pLa->len >= pLa->listsize)

	{

		newsize = (int *)realloc(pLa->arry, (pLa->listsize + LISTINCREMENT) * sizeof(int));

 

 

		if (!newsize)

			exit(OVERFLOW);

 

 

		pLa->arry = newsize;

		ExpandList(pLa);

 

 

	}

 

 

	q = &pLa->arry[place - 1];

 

 

	for (p = &pLa->arry[pLa->len - 1]; p >= q; --p)

		* (p + 1) = *p;

 

 

	*q = math;

	++pLa->len;

 

 

	return OK;

}//向线性表中指定位置插入指定元素

 

 

int ListDelete(SqList * pLa, int place)

{

	int *p, *q;

 

 

	if (place < 1 || place > pLa->len)

		return ERROR;

 

 

	p = &(pLa->arry[place - 1]);

	q = pLa->arry + pLa->len - 1;

 

 

	for (++p; p <= q; ++p)

		*(p - 1) = *p;

 

 

	--pLa->len;

 

 

	return OK;

}//删除线性表指定元素

 

 

void EmptyList(SqList *pLa)

{

	free(pLa->arry);

	pLa->listsize = 0;

 

 

 

 

}//把线性表置为空表

 

 

int main(void)

{

	SqList La;

 

 

	NewList(&La);

	ListInPut(&La);

	ListDelete(&La, 3);

	ListInsert(&La, 2, 10);

	ListOutPut(&La, La.len);

	EmptyList(&La);

}
