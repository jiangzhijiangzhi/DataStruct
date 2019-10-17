#include"stdio.h"
#include"stdlib.h"
#include"time.h"

typedef struct node{
	int data;
	struct node *prior;
	struct node *next;
}Node,*linklist;

linklist creat(int n);
void print(linklist head);
void searc(linklist head);
void del(linklist head);

int main()
{
	linklist head;
	head=creat(5);
	print(head);
	searc(head);
	del(head);
	printf("There are the rest of the data:\n");
	print(head);
	return 0;
}

linklist creat(int n){
	linklist h,p1,p2;
	h=(linklist)malloc(sizeof(node));
	p2=h;
	srand(time(NULL));
	for(int i=0;i<n;i++){
		p1=(linklist)malloc(sizeof(node));
		p1->data=rand();
		p2->next=p1;
		p1->prior=p2;
		p2=p1;
	}
	p2->next=NULL;
	return(h);
}

void print(linklist head){
	linklist p;
	p=head->next;
	if(head!=NULL)
		do{
			printf("%d ",p->data);
			p=p->next;
		}while(p!=NULL);
		printf("\n");
}

void searc(linklist head){
	linklist p;
	int x=0,m;
a:	printf("please enter the number you want to find:\n");
	scanf("%d",&m);
	p=head->next;
	if(head!=NULL)
		do{
			if(p->data==m){
			printf("Yes,it exists in this linked list.\n");
			x=1;
			}
			p=p->next;
		}while(p!=NULL);
	if(x==0){
	printf("NO,it doesn't exists in this linked list.\n");
	goto a;
	}
}

void del(linklist head){
	linklist p;
	int x=0,n;
b:	printf("please enter the number you want to delete:\n");
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
	printf("Sorry,it doesn't exists in this linked list.\n");
	goto b;
	}
}
