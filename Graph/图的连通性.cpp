#include "stdio.h"
#include "math.h"
#include"malloc.h"
#include "stack"
#include <iostream>
#define OK 1
#define ERROR -1
#define MAX 65535
#define STACK_INIT_SIZE  100
#define TRUE  1
#define FALSE 0
#define MAX_VERTEX_NUM 20
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
VertexType GetVex(MGraph G,int v) {

	if(v >= G->vexnum || v < 0)
		exit(ERROR);
	return G->vexs[v];
}
void DFSTree (MGraph G,int v,CSTree &T) //7.8
{
	CSTree p,q;
	int first,visited[50];
	visited[v] = TRUE;
	first = TRUE;
	for(int w=FirstAdjVex(G,v); w>=0; w=NextAdjVex(G,v,w))
	if(!visited[w]){
       p=(CSTree)malloc(sizeof(CSNode));//分配孩子结点
       //*p={GetVex(G,v),NULL,NULL};
	   if(!p)exit(OVERFLOW);
	   p->data=GetVex(G,w);
	   p->rchild=NULL;
	   p->lchild=NULL;
       if(first)//w是v的第一个未被访问的邻接顶点，作为根的左孩子结点
       {
       	T->lchild=p;
		first=FALSE;
       }
       else{//w是v的其他未被访问的邻接顶点，作为上一邻接顶点的右兄弟
       	q->nextsibling=p;
       }
       q=p;
       DFSTree(G,w,p);//从第w个顶点出发深度优先遍历图G，建立生成子树q
	}
}
void DFSForest(MGraph G,CSTree &T)  //7.7 
{
	CSTree p,q;
	int v;
	T=NULL;
	for(v=0;v<G->vexnum;++v)
	visited[v]=FALSE;
	for(v=0;v<G->vexnum;++v){
	if(!visited[v])//顶点为v的新的生成树的根节点
	{
		p=(CSTree)malloc(sizeof(CSNode));//分配根节点
		//p={Getvex(G,v),NULL,NULL};//根节点赋值
		if(!p)exit(OVERFLOW);
		p->data=GetVex(G,v);
		p->rchild=NULL;
		p->lchild=NULL;
		
		if(!T) T=p;//T是第一课生成树的根
		else q->nextsibling=p;//前一棵的根的兄弟是其他生成树的根
		q = p;//q指示当前生成树的根
		DFSTree(G,v,p);//建立以p为根的生成树
		} 
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
