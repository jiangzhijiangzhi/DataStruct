#include "stdio.h"
#include "math.h"
#include"malloc.h"
#include "stack"
#include <queue>
#include <iostream>
#define OK 1
#define ERROR -1
#define MAX 65535
#define STACK_INIT_SIZE  100
#define STACKINCREMENT  10 
#define TRUE  1
#define FALSE 0
#define MAX_VERTEX_NUM 20
#define INFINITY INT_MAX        //FLOAT_MAX 
#define MAX_NAME 50
using namespace std;

typedef enum {DG, DN, AG, AN} GraphKind; //{有向图,有向网,无向图,无向网}
typedef int status;
typedef int VRType;
typedef int InfoType;
typedef char VertexType;
typedef char TElemType;
typedef char QElemType;

char visited[MAX_NAME];
typedef struct Gnode{
	char vexs[MAX_VERTEX_NUM];
	int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int vexnum;
	int arcnum;
}Gnode,*MGraph;

typedef struct CSNode{
 TElemType        data;
 struct CSNode    *firstchild,*nextsibling,*lchild,*rchild;
} CSnode, *CSTree;
typedef struct ArcNode          /* 弧结点的结构 */
{
 int    adjvex;                 /* 该弧所指向的顶点的位置 */
 struct ArcNode *nextarc;       /* 指向下一条弧的指针 */
 int    weight;                 /* 如权值 */
}ArcNode;

int Getvexs(MGraph G,int v)
{return v;}

MGraph Inint (MGraph G,int v) //初始化图
{
	int i,j;
	for(i=0;i<v;i++)
	for(j=0;j<v;j++)
	{
		if(i==j) G->arcs[i][j]=0;
		else G->arcs[i][j]=MAX;
	}
	
} 
MGraph Creategraph(int num)
{
	MGraph G= (MGraph)malloc(sizeof(Gnode));
	if(G==NULL) 
	{cout<<"error"; return NULL;}
	int Enum,v,e;
	Inint(G,num);
	printf("输入顶点信息：\n");
	for(int i=0;i<G->vexnum;i++)
	cout<<G->vexs[i];
	 int k;
	 cout<<"输入边数"<<" ";
	 fflush(stdin);
	 cin>>Enum;
	 cout<<"输入各边和权值"<<" ";
	 int i,j,w;
	 for(e=0;e<Enum;e++);
	 {
 		cin>>i;cin>>j;cin>>w;
		 G->arcs[i][j]=w;
		 G->arcs[i][j]=G->arcs[j][i]; 
 	} 
}

int FirstAdjVex(MGraph G,int v)
{
	int i;
	for(i=0;i<G->vexnum;i++)
		if(G->arcs[v][i]==1)return i;
	return -1;
}
int NextAdjVex(MGraph G,int v,int w)
{
	int j;
	for(j=w+1;j<G->vexnum;j++)
	if(G->arcs[v][j]==1)return j;
	return -1;
}
void DFSTree (MGraph G,int v,CSTree &T) //7.8
{
	CSnode q;
	CSTree p;
	int first,visited[50];
	visited[v] = OK;first = OK;
	for(int w=FirstAdjVex(G,v); w>=0; w=NextAdjVex(G,v,w))
	if(!visited[w]){
       p=(CSTree)malloc(sizeof(CSNode));
       *p={GetVex(G,v),NULL,NULL};
       
       if(first)
       {
       	T->lchild;first=FALSE;
       }
       else{
       	q->nextsibling=p;
       }
       q=p;
       DFSTree (&G,w,p);
	}
}
void DFSForest(MGraph G,CSTree &T)  //7.7 
{
	CSTree p,q;
	int v;
	char visited[50];
	T=NULL;
	for(int v=0;v<G->vexnum;++v)
	visited[v]=FALSE;
	for(v=0;v<G->vexnum;++v)
	if(!visited[v])
	{
		p=(CSTree)malloc(sizeof(CSNode));
		*p={Getvex(G,v),NULL,NULL};
		if(!T) T=p;
		else q->nextsibling=p;
		q = p;
		DFSTree(G,v,p);
	} 
}

int main()
{
		MGraph G;
		CSTree T;
		int Vnum;
		printf("请输入顶点个数: \n");
		scanf("%d",&Vnum);
		G = Creategraph(Vnum);
		printf("建图结果:\n");
		DFSForest(G,T);
		DFSTree(G,Vnum,T);
		return 0;	
}
