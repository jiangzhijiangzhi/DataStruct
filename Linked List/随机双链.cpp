#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef int ElemType;
typedef int Status;
typedef struct DulNode{
	ElemType data;
	struct DulNode *prior;
	struct DulNode *next;
}DulNode,*DuLinkList;
DuLinkList CreateList_DuL(int n){
	DuLinkList h,p,s;
	h=(DuLinkList)malloc(sizeof(DulNode));
	s=h;
	srand(time(NULL));
	for(int i=0;i<n;i++){
	p=(DuLinkList)malloc(sizeof(DulNode));
	p->data=rand();
	s->next=p;
	p->prior=s;
	s=p;
	}
	s->next=NULL;
	return(h);
} //���� 
void PrintList_DuL(DuLinkList head){
	DuLinkList p;
	p=head->next;
	if(head!=NULL)
		do{
			printf("%d ",p->data);
			p=p->next;
		}while(p!=NULL);
		printf("\n");
}//��ӡ 
void SearcList_DuL(DuLinkList head){
	DuLinkList p;
	int x=0,m;
a:	printf("�����������ѯ������:\n");
	scanf("%d",&m);
	p=head->next;
	if(head!=NULL)
		do{
			if(p->data==m){
			printf("�����ݴ��ڡ�\n");
			x=1;
			}
			p=p->next;
		}while(p!=NULL);
	if(x==0){
	printf("��Ǹ�������ݲ����ڣ�\n");
	goto a;
	}
}//���� 
void DeleteList_DuL(DuLinkList head){
	DuLinkList p;
	int x=0,n;
b:	printf("����������ɾ��������:\n");
	scanf("%d",&n);
	p=head->next;
	if(head!=NULL)
		do{
			if(p->data==n){
				x=1;
				p->prior->next=p->next;
				if((p->next)==NULL)break;
				p->next->prior=p->prior;
			}
			p=p->next;
		}while(p!=NULL);
	if(x==0){
	printf("��Ǹ�������ݲ����ڣ�\n");
	goto b;
	}
}//ɾ�� 
int main(){
	DuLinkList head;
	head=CreateList_DuL(6);
	PrintList_DuL(head);
	SearcList_DuL(head);
	DeleteList_DuL(head);
	printf("ɾ���ɹ���ʣ���������:\n");
	PrintList_DuL(head);
	return 0;
}
