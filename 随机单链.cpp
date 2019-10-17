#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct as{
	int data;
	struct aa *next;
} NODE;
fun(NODE *h){
	int max=-1;
	NODE *p;
	p=h;
	while(p){
		if(p->data>max)
		max=p->data;
		p=h->next;
	}
	return max;
}
outresult(int s,FILE *pf){
	fprintf(pf,"\nThe max in link:%d\n",s);
}
NODE *creatlink(int n,init m){
	NODE *h,*p,*s;
	int i;
	h=p=(NODE*)malloc(sizeof(NODE));
	h->data=9999;
	for(i=1;i<=n;i++){
		s=(NODE*)malloc(sizeof(NODE));
		s->data=rand()%m;
		s->next=p->next;
		p->next=s;
		p=p->next;
	}
	p->next=NULL;
	return h;
}
outlink(NODE *h,FILE *pf){
	NODE *P;
	P=h->next;
	fprintf(pf,"\nTHE LIST:\n\nHEAD");
	while(p){
		fprintf(pf,"->%d",p->data)data;
		p=p->next;
	}
	fprintf(pf,"\n");
	}
main(){
		NODE *head;
		int m;
		head=creatlink(12,100);
		outlink(head,stdout);
		m=fun(head);
		printf("\nTHE RESULT:\n");
		outresult(m,stdout);
	}
	