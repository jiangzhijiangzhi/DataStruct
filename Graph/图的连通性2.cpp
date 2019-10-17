#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mgraph.h"
using namespace std;
Status CreateGraph(MGraph *G) {
	printf("please enter the kind of the graph:");
	scanf("%d",&(*G).kind);
	switch((*G).kind) {
		case UDG:
			return CreateUDG(G);
			break;
		case DG:
			return CreateDG(G);
		case UDN:
			return CreateUDN(G);
			break;
		case DN:
			return CreateDN(G);
			break;
		default:
			return ERROR;
	}

}	

Status DFSTraverse(MGraph G,Status (*Visit) (VertexType)) {
	int i;
	//初始化访问记录数组
	for(i = 0;i < G.vexnum; i++)
		visited[i] = FALSE;
	for(i = 0;i < G.vexnum ; i++) 
		if(!visited[i])
			DFS(G,i,Visit);
	return OK;
}

void DFS(Graph G,int v)
{
    visited[v]=TRUE;VisitFunc(v);
    for(w=FristAdjVex(G,v);w>=0;w=NextAdjVex(G,v,w))
        if(!visited[w]) DFS(G,w);
}

VertexType GetVex(MGraph G,int v) {
	
	if(v >= G.vexnum || v < 0)
		exit(ERROR);
	return G.vexs[v];
}

void DFSForest(Graph G,CSTree &T)
{
    int v;
    T=NULL;
    for(v=0;v<G.vexnum;++v)
        visited[v]=FALSE;
    for(v=0;v<G.vexnum;++v)
        if(!visited[v])
        {p=(CSTree)malloc(sizeof(CSNode));
        *p={GetVex(G,v),NULL,NULL};
        if(!T) T=p;
        else q->nextsibling=p;
        q=p;
        DFSTree(G,v,p);
	}
}

void DFSTree(MGraph G,int v,BiTree *T) {
	BiTree p,q;
	int first,w;
	p = q = NULL;
	visited[v] = TRUE;
	first = TRUE;
	for(w = FirstAdjVex(G,GetVex(G,v)); w >= 0 ; w = NextAdjVex(G,GetVex(G,v),GetVex(G,w))) {
		if(!visited[w]) {
			p = (BiTree) malloc(sizeof(struct BiTNode));
			if(!p)
				exit(OVERFLOW);
			p->data = GetVex(G,w);
			p->rchild = NULL;
			p->lchild = NULL;
			if(first) {
				(*T)->lchild = p;
				first = FALSE;
			}
			else
				q->rchild = p;
			q = p;
			DFSTree(G,w,&q);
		}
	}
}

int main(int argc, char* argv[])
{
    printf("Hello World!\n");
    return 0;
}
