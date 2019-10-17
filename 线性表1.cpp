#include<stdio.h>
#include<stdlib.h>
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 50//���Ա�洢�ռ��ʼ������
#define LISTINCERMENT 10//���Ա�Ĵ���ռ�ķ�������
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
}//����һ���յ����Ա�

void ExpandList(SqList &L)
{
	L.listsize += LISTINCERMENT;
}//�����ĵ�ǰ����

void ListInput(SqList &L)
{
	int i, length;
	int flow_control;
	int temp = 0;
	printf("��������Ҫ������ٸ�����!\n");
	scanf("%d", &length);
	if(length>L.listsize)
	{
	printf("�����������!\n��Ҫ������?\n��Ҫ�밴1\n����Ҫ�밴0\n");
	scanf("%d", &flow_control);
		while (0)
		{
		switch (flow_control)
			{
			case 0:exit(ERROR); break;
			case 1:ExpandList(L); break;
			default:printf("�����������!\n"); break;
			}
		}
	}
 	else
	{
		for (i=0;i<length;i++)
		{
			printf("�������%d������\n", i + 1);
			scanf("%d", &L.arry[i]);
			++L.length;
			--L.listsize;
		}
	}
}//�����Ա���������

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
}//�����Ա����ݰ����������� 

 void ListOutput(SqList &L,int length){
	for(int i=0;i<L.length;i++)printf("%d",L.arry[i]);
}//������Ա�����

int main(){
	SqList L;
	InitList(L);
	ListInput(L);
	ListSort(L);
	ListOutput(L,L.length);
	printf("\n");
}
