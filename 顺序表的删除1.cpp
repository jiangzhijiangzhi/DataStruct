#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 1000
#define LISTINCREMENT 10
#define ERROR 0
#define OK 1
#define OVERFLOW -1
typedef int ElemType;
typedef int Status;
typedef struct{
	ElemType *elem;
	int length;
	int listsize;
}SqList;
Status InitList_Sq(SqList &L){
	L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!L.elem)
		exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
void ListInput_Sq(SqList &L,int n){
	int i;
	ElemType *p;
	p=&L.elem[0];
	for(i=0;i<n;i++){
		scanf("%d",p++);
	}
	L.length=n;
}
Status ListDelete_Sq(SqList &L,int i,ElemType &e){
	ElemType *p,*q;
	if(i<1||i>L.length)return ERROR;
	p=&L.elem[i-1];
	e=*p;
	q=L.elem+L.length-1;
	for(++p;p<=q;++p)
	*(p-1)=*p;
	--L.length;
	return OK;
}
int main(){
	int i,q,n,k;
	SqList L;
	ElemType e;
	InitList_Sq(L);
	while(scanf("%d",&n)!=EOF){
		ListInput_Sq(L,n);
		scanf("%d",&q);
		for(i=1;i<=q;i++){
			scanf("%d",&k);
			if(ListDelete_Sq(L,k,e)==ERROR)
			printf("-1\n");
			else printf("%d\n",e);
		}
	}
	return 0;
}
