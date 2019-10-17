#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include <direct.h>
#include <limits.h>
#include <vector>
#include <algorithm>
#include <iomanip>

#define OK  1
#define ERROR 0
#define MAX_VERTEXT_NUM 20
#define INFINITY INT_MAX        //FLOAT_MAX 
using namespace std;

typedef enum {UDG=0,UDN=1,DG=2,DN=3} GraphKind;//无向图，无向网，有向图，有向网 
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


int readAdjMetrixdata(GraphKind kd,MGraph &G)//////////////************************/////////////
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
   {if(!(strchr(buff,lBraket)||strchr(buff,',')))
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
    else if (kd==DN)
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
   {if(!(strchr(buff,lBraket)||strchr(buff,',')))
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

int main()
{
 MGraph mg;
 ALGraph alg;
/*
 CreateAdjMetrix("无向图7_3.txt",UDG,mg);
 displayAdjMetrix(mg);
 destroyMGraph(&mg);  

 CreateAdjList("无向图7_3.txt",UDG,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);
 */

 CreateAdjMetrix("无向网7_16.txt",UDN,mg);
 displayAdjMetrix(mg);
 destroyMGraph(&mg); 
 
 CreateAdjList("无向网7_16.txt",UDN,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);

 return 0;
}