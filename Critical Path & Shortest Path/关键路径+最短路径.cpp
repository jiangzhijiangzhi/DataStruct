#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <direct.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stack>

#define OK  1
#define ERROR 0
#define MAX_VERTEXT_NUM 20
#define INFINITY 65535            //FLOAT_MAX 
//#define INFINITY INT_MAX        //FLOAT_MAX 
using namespace std;

typedef enum {UDG=0,UDN=1,DG=2,DN=3} GraphKind;//无向图，无向网，有向图，有向网 
typedef stack<int> IntStack;
//×××××××××××××××××××××××××××××××××××××××××××××× 
//×图的数据文件构成：两部分组成                                                            ×
//×第一部分：顶点信息：目前只支持3长度的字符串                                             × 
//×          每个串单占一行                                                                ×
//×第二部分：边的信息（每条边单占一行）                                                    × 
//×          ①无向图：(顶点名称1,顶点名称2)                                               × 
//×          ②无向网：(顶点名称1,顶点名称2)权值                                           × 
//*           ③有向图：<顶点名称1,顶点名称2>                                               *
//*           ④有向图：<顶点名称1,顶点名称2>权值                                           *
//××××××××××××××××××××××××××××××××××××××××××××××

typedef string VertexType;     // 顶点的类型 
typedef int VRType;             //VRType是顶点关系类型。无权图，用1或0；带权图，则为权值。 
//============================================================
//=                          邻接矩阵                        =
//   结构 ：此处直接定义了邻接矩阵为VRType类型的二维数据     =
//============================================================
typedef struct{
 vector <VertexType> vexs;
 vector <vector <VRType> > arcs;
 int vexnum,arcnum;
 GraphKind kind; 
} MGraph;
//========================================================================= 
//= 通过指定文件来创建邻接矩阵                                            = 
//= 其中filename文件要与指定的此程序的源码放在同一目录中                  = 
//========================================================================= 
int CreateAdjMetrix(char * filename,GraphKind kd,MGraph &G); 

//-------------------------------------------------------------------------
//-                                  邻接表                               -
//-                                                                       -
//------------------------------------------------------------------------- 
typedef struct ArcNode          /* 弧结点的结构 */
{
 int    adjvex;                 /* 该弧所指向的顶点的位置 */
 struct ArcNode *nextarc;       /* 指向下一条弧的指针 */
 int    weight;                 /* 如权值 */
}ArcNode;


typedef struct VNode            /* 顶点结点的结构 */
{
 VertexType data;               /* 顶点信息 */
 ArcNode   *firstarc;           /* 指向第一条依附该顶点的弧的指针 */
}VNode;

typedef struct                  /* 图的邻接表结构定义 */
{
 vector<VNode> vexs;            /* 存放顶点的数组 */
 int        vexnum, arcnum;     /* 图的当前顶点数和弧数 */
 GraphKind  kind;               /* 图的种类标志 */
}ALGraph;
//--------------------------------------------------------------------------------------------
//-面向对象:重载                                                                             - 
//--------------------------------------------------------------------------------------------
int LocateVex(MGraph G ,VertexType u);//邻接矩阵中查顶点名称u是否存在，存在则返回下标，否则为-1 
int LocateVex(ALGraph G,VertexType u);    //邻接表中查顶点名称u是否存在，存在则返回下标，否则为-1 

int CreateAdjMetrix(char * filename,GraphKind kd,MGraph &G); //创建邻接矩阵 
void displayAdjMetrix(MGraph G);                             //打印邻接矩阵 
void destroyMGraph(MGraph *G);                               //销毁邻接矩阵

int CreateAdjList(char * filename,GraphKind kd,ALGraph &G);//创建邻接表 
int PrintALGraph(ALGraph *G);                              //打印邻接表
int DestroyALGraph(ALGraph *G);                            //销毁邻接表 
 
void ShortestPath_DIJ(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM]);   //单源最短路径 
void PrintShortestPath(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM]);  //打印最短路劲 

void FindInDegree(ALGraph G, int *indegree);  //计算入度 
int TopologicalOrder(ALGraph G, IntStack &T); //求解拓扑序列和逆序 
int CriticalPath(ALGraph G);                  //求解关键路径 
//---------------------------------------------
//- 公用：打开指定文件                        -    
//---------------------------------------------
FILE * OpenDataFile(char * filename) 
{
 int j;
 char *p;
 FILE *myfile;
 char szFullPath[MAX_PATH];
 GetModuleFileName(NULL,szFullPath,MAX_PATH);
 j=strlen(szFullPath)-1;
 while(j>0 && szFullPath[j]!='\\')
   j--;
 p=&szFullPath[j+1];
 strcpy(p,filename);
 myfile=freopen(szFullPath,"r",stdin); 
 if( myfile == NULL )
    fprintf( stdout, "文件名错误!/n" );
 return myfile;
}
int filterstr(char *str)
{int i=0,index=0;
 
 while(str[index])
  {if(str[index]>' ')
     {
	  str[i]=str[index];
	  i++;
	  }
   index++;
  }
  str[i]='\0';
  return(strlen(str));
}

/* 初始条件:图G存在,u和G中顶点有相同特征 */  
/* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */  
int LocateVex(MGraph G,VertexType u)  
{int i;
 for(i=0;i<G.vexnum;++i)  
    if(G.vexs[i].compare(u)==0)  
            return i;  
    return -1;  
} 

int LocateVex(ALGraph G,VertexType u)  
{int i;
 for(i=0;i<G.vexnum;++i)  
    if(G.vexs[i].data.compare(u)==0)  
            return i;  
    return -1;  
}
//========================================================================= 
//= 通过指定文件来创建邻接表                                              = 
//= 其中filename文件要与指定的此程序的源码放在同一目录中                  = 
//========================================================================= 
int CreateAdjList(char * filename,GraphKind kd,ALGraph &G); 


int readAdjMetrixdata(GraphKind kd,MGraph &G)
{
 char lBraket,rBraket,decollator[4]={','};
 char buff[80],strw[10];
 char *result = NULL;
 VertexType vexspair[2];
 int first,i,j;
 
 if (kd==UDN ||kd==UDG)
      {lBraket='(';rBraket=')'; }
 else {lBraket='<';rBraket='>'; }
 decollator[1]=lBraket;
 decollator[2]=rBraket;
 //顶点信息部分
 while (gets(buff))
   {if(!filterstr(buff))
       continue;
    if(!(strchr(buff,lBraket)||strchr(buff,',')))
      {
       G.vexs.push_back(strupr(buff));
      } 
   	else
        break;
   }
//边信息部分 
   G.vexnum=G.vexs.size();  	
   G.arcs.resize(G.vexs.size());
   for (i=0;i<G.vexnum;i++)
        {G.arcs[i].resize(G.vexnum);
         for (j=0;j<G.vexnum;j++)
             if (kd==UDG || kd==DG)
                G.arcs[i][j]=0;
             else
                G.arcs[i][j]=INFINITY;
        }
   first=0;
   do{
   	  if(!filterstr(buff))
       continue;
      result=NULL;
      i=0;
      result = strtok( buff, decollator );
      while( result != NULL &&i<=2) {
        	if (i<2)
        	     vexspair[i]=strupr(result);
 	        i++;
 	        if(i==3)
               strcpy(strw,result);    
            result = strtok( NULL, decollator );
         }
   i=LocateVex(G,vexspair[0]); 
   j=LocateVex(G,vexspair[1]); 
   if (i<0||j<0)
       {cout<<"顶点对:"<<vexspair[0]<<','<<vexspair[1]<<"错误！"<<endl; 
	    continue;
       }
   if(kd==UDG)
        {G.arcs[i][j]=1;
		 G.arcs[j][i]=1;
		 }
    else if (kd==UDN)
         {G.arcs[i][j]=atoi(strw);
		  G.arcs[j][i]=G.arcs[i][j];
         }
    else if (kd==DG)
	     G.arcs[i][j]=1;
    else G.arcs[i][j]=atoi(strw);
    first++; 
   }while (gets(buff));
   G.arcnum=first; 
}

/* 输出邻接矩阵G */  
void displayAdjMetrix(MGraph G)  
{  
    int i,j,nwidth=6;  
    char s[7],s1[3];  
    switch(G.kind)  
    {  
    case DG:  
        strcpy(s,"有向图\0");  
        strcpy(s1,"弧\0");  
        break;  
    case DN:  
        strcpy(s,"有向网\0");  
        strcpy(s1,"弧\0");  
        nwidth=12;
        break;  
    case UDG:  
        strcpy(s,"无向图\0");  
        strcpy(s1,"边\0");  
        break;  
    case UDN:  
        strcpy(s,"无向网\0");  
        strcpy(s1,"边\0");  
        nwidth=12;
        break;  
    }  
    printf("%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);  
    for(i=0;i<G.vexnum;++i) /* 输出G.vexs */  
        cout<<"G.vexs["<<i<<"]="<<G.vexs[i]<<endl; //printf("G.vexs[%d]=%s\n",i,G.vexs[i]); 此用法错误 
    cout<<"G.arcs:\n"; /* 输出G.arcs */  
    for(i=0;i<G.vexnum;i++)  
    {  
        for(j=0;j<G.vexnum;j++)  
            cout<<setw(nwidth)<<G.arcs[i][j];  
        cout<<endl;  
    }  
 }  
/*初始化条件:图G存在*/  
/*操作结果:销毁图G*/  
void destroyMGraph(MGraph *G)  
{  
    int i;  
    for (i=0;i<G->vexs.size();i++)
        G->arcs[i].clear();
    G->vexs.clear();
    G->arcs.clear();
    (*G).vexnum=0;  
    (*G).arcnum=0;  

    cout<<"图销毁成功!"<<endl;  
} 
//========================================================================= 
//= 通过指定文件来创建邻接矩阵                                            = 
//= 其中filename文件要与指定的此程序的源码放在同一目录中                  = 
//========================================================================= 
int CreateAdjMetrix(char * filename,GraphKind kd,MGraph &G) 
{
 FILE * datafile;
 datafile=OpenDataFile(filename);
 if (datafile)
   {
   	G.kind=kd;
   	readAdjMetrixdata(kd,G);
    fclose(datafile);
   }
}

int readAdjListdata(GraphKind kd,ALGraph &G)
{
 char lBraket,rBraket,decollator[4]={','};
 char buff[80],strw[10],bakbuf[80];
 char *result = NULL;
 VNode vex;
 VertexType vexspair[2];
 int first,i,j;
 ArcNode   *p,   *q;   
 
 if (kd==UDN ||kd==UDG)
      {lBraket='(';rBraket=')'; }
 else {lBraket='<';rBraket='>'; }
 decollator[1]=lBraket;
 decollator[2]=rBraket;
 //顶点信息部分
 while (gets(buff))
   {if(!filterstr(buff))
       continue;
    if(!(strchr(buff,lBraket)||strchr(buff,',')))
      {vex.data=strupr(buff);
       vex.firstarc=NULL;
       G.vexs.push_back(vex);
      } 
   	else
        break;
   }
//边信息部分 
   G.vexnum=G.vexs.size();  	
   first=0;
   do{
      if(!filterstr(buff))
        continue;
      result=NULL;
      i=0;
      strcpy(strw,"");
      strcpy(bakbuf,strupr(buff));
      result = strtok( bakbuf, decollator );
      while( result != NULL &&i<=2) {
        	if (i<2)
        	     vexspair[i]=strupr(result);
 	        i++;
            if(i==3)
                strcpy(strw,result);
            result = strtok( NULL, decollator );
         }

   i=LocateVex(G,vexspair[0]);
   j=LocateVex(G,vexspair[1]);

   if (i<0||j<0)
       {cout<<"顶点对:"<<vexspair[0]<<','<<vexspair[1]<<"错误！"<<endl; 
	    continue;
       }
   p=(struct ArcNode   *)malloc(sizeof(struct   ArcNode));
   p->adjvex  =j;   /* 保存该弧所指向的顶点位置 */
   p->nextarc =G.vexs[i].firstarc;   
   G.vexs[i].firstarc = p;   
   if(kd==UDG||kd==UDN)
      {   
         q=(struct ArcNode   *)malloc(sizeof(struct   ArcNode));   
         q->adjvex  =   i;   /* 保存该弧所指向的顶点位置 */
         q->nextarc =   G.vexs[j].firstarc; 
         if(kd==UDN)
       		 q->weight  =atoi(strw);  
         G.vexs[j].firstarc =q;   
      }
    if(kd==UDN||kd==DN)
	   p->weight=atoi(strw);
    first++;
   }while (gets(buff));
   G.arcnum=first; 
}

//================================================================
//=                      建邻接表                                =
//================================================================
int CreateAdjList(char * filename,GraphKind kd,ALGraph &G)
{ 
 FILE * datafile;
 datafile=OpenDataFile(filename);
 if (datafile)
   {
   	G.kind=kd;
   	readAdjListdata(kd,G);
    fclose(datafile);
   }
 return OK;
}  
//================================================================
//=                      打印邻接表                              =
//================================================================
int PrintALGraph(ALGraph *G)     
{
 int i;
 struct ArcNode *p;
 char lBraket,rBraket;
 if (G->kind==UDN ||G->kind==UDG)
      {lBraket='(';rBraket=')'; }
 else {lBraket='<';rBraket='>'; }
 cout<<"打印"<<((G->kind==UDG)?"无向图":(G->kind==UDN)?"无向网":(G->kind==DG)?"有向图":"有向网")<<endl;
 for(i=0 ; i <G->vexnum ; i++)
 {
  cout<<"顶点号："<<setw(3)<<i<<"  名称："<<G->vexs[i].data<<"  邻接:";
  p=G->vexs[i].firstarc;
  while(p != NULL)
  {
   cout<<setw(3)<<p->adjvex;
   if (G->kind==UDN||G->kind==DN)
       cout<<':'<<lBraket<<p->weight<<rBraket;
   p=p->nextarc;
  }
  cout<<endl;
 }
 cout<<"顶点共"<<G->vexnum<<"个\t" <<"边共"<<G->arcnum<<"条"<<endl; 
 return OK;
}
//================================================================
//=                      销毁邻接表                              =
//================================================================
int DestroyALGraph(ALGraph *G)     
{
 int i;
 struct ArcNode *p,*q;
 for(i=0 ; i <G->vexnum ; i++)
 {
  p=G->vexs[i].firstarc;
  while(p!= NULL)
  {q=p;
   p=p->nextarc;
   free(q);
  }
 }
 G->vexs.clear();
 G->vexnum=0;
 G->arcnum=0;
 cout<<"图销毁成功!"<<endl;  
 return OK;
}

//-------------------------------------------------------
 //                     关键路径测试                     - 
 //------------------------------------------------------- 
void FindInDegree(ALGraph G, int *indegree)
 {
	 int i,k;
	 ArcNode *p;    	 
	 for (i=0; i<G.vexnum; ++i)
	 {
	    for (p=G.vexs[i].firstarc;  p;  p=p->nextarc) {
			{k = p->adjvex;indegree[k]++;  }              
		}
 	 }
 }
 
int ve[MAX_VERTEXT_NUM]={0},vl[MAX_VERTEXT_NUM]={0};
int TopologicalOrder(ALGraph G, IntStack &T) {  // 算法7.13
  // 有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve(全局变量)。
  // T为拓扑序列定点栈，S为零入度顶点栈。
  // 若G无回路，则用栈T返回G的一个拓扑序列，且函数值为OK，否则为ERROR。
  IntStack S;
  int count=0,k,j;
  int indegree[40]={0};
  ArcNode *p;
  FindInDegree(G, indegree);  // 对各顶点求入度indegree[0..vernum-1]
  for (int j=0; j<G.vexnum; ++j)     // 建零入度顶点栈S
    if (indegree[j]==0) S.push(j);  // 入度为0者进栈
  //建拓扑序列顶点栈T
  count = 0;  
  for(int i=0; i<G.vexnum; i++) ve[i] = 0;  // 初始化
  while (!S.empty()) {
    j=S.top();S.pop();
	T.push(j);
	++count;       // j号顶点入T栈并计数
    for (p=G.vexs[j].firstarc;  p;  p=p->nextarc) {
      k = p->adjvex;            // 对j号顶点的每个邻接点的入度减1
      if (--indegree[k] == 0) S.push(k);   // 若入度减为0，则入栈
      if (ve[j]+p->weight> ve[k])  ve[k] = ve[j]+p->weight;
    }//for  *(p->info)=dut(<j,k>)
  }//while
  if (count<G.vexnum) return ERROR;  // 该有向网有回路
  else return OK;
} // TopologicalOrder

int CriticalPath(ALGraph G) {  // 算法7.14
  // G为有向网，输出G的各项关键活动。
  IntStack T;
  int a,j,k,el,ee,dut;
  char tag;
  ArcNode *p;
  if (!TopologicalOrder(G, T)) return ERROR;
  for(a=0; a<G.vexnum; a++)
    vl[a] = ve[G.vexnum-1];    // 初始化顶点事件的最迟发生时间
  while (!T.empty())       // 按拓扑逆序求各顶点的vl值
    for (j=T.top(),T.pop(), p=G.vexs[j].firstarc;  p;  p=p->nextarc) {
      k=p->adjvex;  dut=p->weight;     //dut<j,k>
      if (vl[k]-dut < vl[j]) vl[j] = vl[k]-dut;
    }
  for (j=0; j<G.vexnum; ++j)            // 求ee,el和关键活动
    for (p=G.vexs[j].firstarc;  p;  p=p->nextarc) {
      k=p->adjvex;dut=p->weight;   
      ee = ve[j];  el = vl[k]-dut;
      tag = (ee==el) ? '*' : ' ';
      cout<<'<'<<G.vexs[j].data<<','<<G.vexs[k].data<<"> weight:"<<dut<<" ee:"<<ee<<" el:"<<el<<' '<<tag<<endl;
    }
  return OK;
} // CriticalPath

//-------------------------------------------------------
//                     单源最短路径                     - 
//=------------------------------------------------------ 
int dis[MAX_VERTEXT_NUM]={0},path[MAX_VERTEXT_NUM]={0};
void ShortestPath_DIJ(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM])
{ // 算法7.15
  // 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]
  // 及其带权长度D[v]。
  // 若P[v][w]为TRUE，则w是从v0到v当前求得最短路径上的顶点。
  // final[v]为TRUE当且仅当v∈S,即已经求得从v0到v的最短路径。
  int i=0,j, v,w,min;
  bool final[MAX_VERTEXT_NUM];
  for (v=0; v<G.vexnum; ++v) {
    final[v] = FALSE;  
    D[v] = G.arcs[v0][v];
    if (D[v] < INFINITY) 
	    P[v] = v0;
    else P[v]=-1;
  }
  D[v0] = 0;  final[v0] = TRUE;        // 初始化，v0顶点属于S集
  P[v0]=-1;
   //--- 开始主循环，每次求得v0到某个v顶点的最短路径，并加v到S集 ---
  for (i=1; i<G.vexnum; ++i) {         // 其余G.vexnum-1个顶点
    min = INFINITY;                    // 当前所知离v0顶点的最近距离
    for (w=0; w<G.vexnum; ++w)
      if (!final[w])                           // w顶点在V-S中
        if (D[w]<min) { v = w;  min = D[w]; }  // w顶点离v0顶点更近
    final[v] = TRUE;                       // 离v0顶点最近的v加入S集
    for (w=0; w<G.vexnum; ++w)             // 更新当前最短路径及距离
      if (!final[w] && (min+G.arcs[v][w]<D[w])) { 
        // 修改D[w]和P[w], w∈V-S
        D[w] = min + G.arcs[v][w];
        P[w] = v; 
      }//if
  }//for
} // ShortestPath_DIJ

void PrintShortestPath(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM])
{ int start,v;
  for (v=0; v<G.vexnum; ++v) {
  	  if (v!=v0)
  	     {start=(P[v]!=-1)?D[v]:-1;
  	      cout<<"顶点："<<v0<<"到顶点："<<v<<"最短长度："<<start<<"  路径："; 
  	      start=v;
  	      if (P[v]!=-1)
  	      do{
  	  	       cout<<start<<"<-";
  	  	       start=P[start];
  	      }while(start!=-1);
  	      cout<<endl;
  	     }
  }
}

int main()
{
 MGraph mg;
 ALGraph alg;
//-------------------------------------------------------
//                    单源最短路径测试                  - 
//------------------------------------------------------- 
 CreateAdjMetrix("有向网7_34.txt",DN,mg);
 displayAdjMetrix(mg);
 ShortestPath_DIJ(mg,0,path,dis); 
 PrintShortestPath(mg,0,path,dis);
 destroyMGraph(&mg);  
/*
 CreateAdjList("无向图7_3.txt",UDG,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);
 

 CreateAdjMetrix("无向网7_16.txt",UDN,mg);
 displayAdjMetrix(mg);
 destroyMGraph(&mg); 
 
 CreateAdjList("无向网7_16.txt",UDN,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);
 */
 //-------------------------------------------------------
 //                     关键路径测试                     - 
 //------------------------------------------------------- 
 /*CreateAdjList("有向网7_29.txt",DN,alg);
 PrintALGraph(&alg);
 CriticalPath(alg);
 DestroyALGraph(&alg);
 return 0;
 */
}