#include"stdio.h"
#include"stdlib.h"
#include"algorithm"
#include"string"
#include<iostream>
using namespace std;
typedef struct node{
	int data;
	struct node *prior;
	struct node *next;
}Node,*linklist;

linklist creat(int n);
void print(linklist h);
linklist oper(linklist h1,linklist h2);
void del(linklist h,int data);

int main()
{
	linklist h,h1,h2;
	int n1,n2;
	FILE *myfile;
	myfile=freopen("F:\\DataStruct\\str\\集合AB.txt","r",stdin);
	if(myfile==NULL){
		fprintf(stdout,"error on freopen\n");
		return 0;
	}
	scanf("%d%d",&n1,&n2);
	h1=creat(n1);
	h2=creat(n2);
	printf("集合A:");print(h1);
	printf("集合B:");print(h2);
	h=oper(h1,h2);
	printf("集合(A-B)U(B-A):");print(h);	
	fclose(myfile);
	return 0;
}

linklist creat(int n){
	linklist h,p1,p2;
	h=(linklist)malloc(sizeof(node));
	scanf("%d",&h->data);
	p2=h;
	for(int i=0;i<n-1;i++){
		p1=(linklist)malloc(sizeof(node));
		scanf("%d",&p1->data);
		p2->next=p1;
		p1->prior=p2;
		p2=p1;
	}
	p2->next=h;
	h->prior=p2;
	return(h);
}

void print(linklist h){
	linklist p;
	p=h;
	do{
		printf("%d ",p->data);
		p=p->next;
	}while(p!=h);
	printf("\n");
}

linklist oper(linklist h1,linklist h2){
	linklist h,p,p1,p2;
	int k;
	h=h1;p2=h2;
	do{
		p1=h1;
		k=0;
		do{
			if(p2->data==p1->data)
			{
				k=1;break;
			}
   			p1=p1->next;
		}while(p1!=h1);
		if(k==0){
			p=(linklist)malloc(sizeof(node));
			p->data=p2->data;
			h1->next->prior=p;
			p->next=h1->next;
			h1->next=p;
			p->prior=h1;
			
		}
		if(k==1){
			
			del(h1,p2->data);
		}
		p2=p2->next;	
	}while(p2!=h2);
	return(h);
}

void del(linklist h,int data){
	 linklist p;
	 p=h;
	 do{
 		if(p->data==data){
		 	p->prior->next=p->next;
		 	p->next->prior=p->prior;
		 }
		 p=p->next;
 	 }while(p!=h);
}