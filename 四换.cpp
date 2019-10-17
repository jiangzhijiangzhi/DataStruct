#include <stdlib.h>
#include <stdio.h>
#define OVERFLOW -2
#define OK 1
#define ERROR 0
#define LIST_INIT_SIZE 50 //���Ա���ռ�ĳ�ʼ������
#define LISTINCERMENT 10 //���Ա�Ĵ���ռ�ķ�������
typedef char ElemType; //��һ��char�����������¶���ΪElemType
typedef struct
{
ElemType *elem; // �洢�ռ��ַ
int length; // ���Ա�ǰ����
int listsize; // ��ǰ����Ĵ洢���� 
} SqList; // �׳� ˳���
typedef int Status;
Status InitList_Sq(SqList &S) //// ����һ���յ����Ա�S��
{
S.elem =(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
if (!S.elem) exit(OVERFLOW); // �洢����ʧ��
S.length = 0; // �ձ���Ϊ0
S.listsize = LIST_INIT_SIZE; // ��ʼ�洢����
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
Status ListInsert_Sq(SqList &S,int i,ElemType X) //�����Ա�S�е�i��λ��֮ǰ����������Ԫ��X��S�ĳ��ȼ�1
{
if(i<1||i>S.length +1)return ERROR;//iֵ���Ϸ�
if(S.length >=S.listsize ) //��ǰ����ռ����������ӷ���
{
ElemType * newbase=(ElemType *)realloc(S.elem,(S.listsize +LISTINCERMENT)*sizeof(ElemType));
if(!newbase)exit(OVERFLOW); //�������ʧ��
S.listsize=S.listsize+LISTINCERMENT; //���Ӵ�������
S.elem=newbase; // �»�ַ
}
ElemType *q=&S.elem[i-1]; //qΪ����λ��
for(ElemType * p=&S.elem[S.length] ;p>=q;p--) *(p+1)=*p; //����λ�ú�Ԫ�غ���
*q=X; //����e
S.length++;//����1
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
