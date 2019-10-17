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

typedef enum {UDG=0,UDN=1,DG=2,DN=3} GraphKind;//����ͼ��������������ͼ�������� 
typedef stack<int> IntStack;
//�������������������������������������������������������������������������������������������� 
//��ͼ�������ļ����ɣ����������                                                            ��
//����һ���֣�������Ϣ��Ŀǰֻ֧��3���ȵ��ַ���                                             �� 
//��          ÿ������ռһ��                                                                ��
//���ڶ����֣��ߵ���Ϣ��ÿ���ߵ�ռһ�У�                                                    �� 
//��          ������ͼ��(��������1,��������2)                                               �� 
//��          ����������(��������1,��������2)Ȩֵ                                           �� 
//*           ������ͼ��<��������1,��������2>                                               *
//*           ������ͼ��<��������1,��������2>Ȩֵ                                           *
//��������������������������������������������������������������������������������������������

typedef string VertexType;     // ��������� 
typedef int VRType;             //VRType�Ƕ����ϵ���͡���Ȩͼ����1��0����Ȩͼ����ΪȨֵ�� 
//============================================================
//=                          �ڽӾ���                        =
//   �ṹ ���˴�ֱ�Ӷ������ڽӾ���ΪVRType���͵Ķ�ά����     =
//============================================================
typedef struct{
 vector <VertexType> vexs;
 vector <vector <VRType> > arcs;
 int vexnum,arcnum;
 GraphKind kind; 
} MGraph;
//========================================================================= 
//= ͨ��ָ���ļ��������ڽӾ���                                            = 
//= ����filename�ļ�Ҫ��ָ���Ĵ˳����Դ�����ͬһĿ¼��                  = 
//========================================================================= 
int CreateAdjMetrix(char * filename,GraphKind kd,MGraph &G); 

//-------------------------------------------------------------------------
//-                                  �ڽӱ�                               -
//-                                                                       -
//------------------------------------------------------------------------- 
typedef struct ArcNode          /* �����Ľṹ */
{
 int    adjvex;                 /* �û���ָ��Ķ����λ�� */
 struct ArcNode *nextarc;       /* ָ����һ������ָ�� */
 int    weight;                 /* ��Ȩֵ */
}ArcNode;


typedef struct VNode            /* ������Ľṹ */
{
 VertexType data;               /* ������Ϣ */
 ArcNode   *firstarc;           /* ָ���һ�������ö���Ļ���ָ�� */
}VNode;

typedef struct                  /* ͼ���ڽӱ�ṹ���� */
{
 vector<VNode> vexs;            /* ��Ŷ�������� */
 int        vexnum, arcnum;     /* ͼ�ĵ�ǰ�������ͻ��� */
 GraphKind  kind;               /* ͼ�������־ */
}ALGraph;
//--------------------------------------------------------------------------------------------
//-�������:����                                                                             - 
//--------------------------------------------------------------------------------------------
int LocateVex(MGraph G ,VertexType u);//�ڽӾ����в鶥������u�Ƿ���ڣ������򷵻��±꣬����Ϊ-1 
int LocateVex(ALGraph G,VertexType u);    //�ڽӱ��в鶥������u�Ƿ���ڣ������򷵻��±꣬����Ϊ-1 

int CreateAdjMetrix(char * filename,GraphKind kd,MGraph &G); //�����ڽӾ��� 
void displayAdjMetrix(MGraph G);                             //��ӡ�ڽӾ��� 
void destroyMGraph(MGraph *G);                               //�����ڽӾ���

int CreateAdjList(char * filename,GraphKind kd,ALGraph &G);//�����ڽӱ� 
int PrintALGraph(ALGraph *G);                              //��ӡ�ڽӱ�
int DestroyALGraph(ALGraph *G);                            //�����ڽӱ� 
 
void ShortestPath_DIJ(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM]);   //��Դ���·�� 
void PrintShortestPath(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM]);  //��ӡ���·�� 

void FindInDegree(ALGraph G, int *indegree);  //������� 
int TopologicalOrder(ALGraph G, IntStack &T); //����������к����� 
int CriticalPath(ALGraph G);                  //���ؼ�·�� 
//---------------------------------------------
//- ���ã���ָ���ļ�                        -    
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
    fprintf( stdout, "�ļ�������!/n" );
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

/* ��ʼ����:ͼG����,u��G�ж�������ͬ���� */  
/* �������:��G�д��ڶ���u,�򷵻ظö�����ͼ��λ��;���򷵻�-1 */  
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
//= ͨ��ָ���ļ��������ڽӱ�                                              = 
//= ����filename�ļ�Ҫ��ָ���Ĵ˳����Դ�����ͬһĿ¼��                  = 
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
 //������Ϣ����
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
//����Ϣ���� 
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
       {cout<<"�����:"<<vexspair[0]<<','<<vexspair[1]<<"����"<<endl; 
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

/* ����ڽӾ���G */  
void displayAdjMetrix(MGraph G)  
{  
    int i,j,nwidth=6;  
    char s[7],s1[3];  
    switch(G.kind)  
    {  
    case DG:  
        strcpy(s,"����ͼ\0");  
        strcpy(s1,"��\0");  
        break;  
    case DN:  
        strcpy(s,"������\0");  
        strcpy(s1,"��\0");  
        nwidth=12;
        break;  
    case UDG:  
        strcpy(s,"����ͼ\0");  
        strcpy(s1,"��\0");  
        break;  
    case UDN:  
        strcpy(s,"������\0");  
        strcpy(s1,"��\0");  
        nwidth=12;
        break;  
    }  
    printf("%d������%d��%s��%s\n",G.vexnum,G.arcnum,s1,s);  
    for(i=0;i<G.vexnum;++i) /* ���G.vexs */  
        cout<<"G.vexs["<<i<<"]="<<G.vexs[i]<<endl; //printf("G.vexs[%d]=%s\n",i,G.vexs[i]); ���÷����� 
    cout<<"G.arcs:\n"; /* ���G.arcs */  
    for(i=0;i<G.vexnum;i++)  
    {  
        for(j=0;j<G.vexnum;j++)  
            cout<<setw(nwidth)<<G.arcs[i][j];  
        cout<<endl;  
    }  
 }  
/*��ʼ������:ͼG����*/  
/*�������:����ͼG*/  
void destroyMGraph(MGraph *G)  
{  
    int i;  
    for (i=0;i<G->vexs.size();i++)
        G->arcs[i].clear();
    G->vexs.clear();
    G->arcs.clear();
    (*G).vexnum=0;  
    (*G).arcnum=0;  

    cout<<"ͼ���ٳɹ�!"<<endl;  
} 
//========================================================================= 
//= ͨ��ָ���ļ��������ڽӾ���                                            = 
//= ����filename�ļ�Ҫ��ָ���Ĵ˳����Դ�����ͬһĿ¼��                  = 
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
 //������Ϣ����
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
//����Ϣ���� 
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
       {cout<<"�����:"<<vexspair[0]<<','<<vexspair[1]<<"����"<<endl; 
	    continue;
       }
   p=(struct ArcNode   *)malloc(sizeof(struct   ArcNode));
   p->adjvex  =j;   /* ����û���ָ��Ķ���λ�� */
   p->nextarc =G.vexs[i].firstarc;   
   G.vexs[i].firstarc = p;   
   if(kd==UDG||kd==UDN)
      {   
         q=(struct ArcNode   *)malloc(sizeof(struct   ArcNode));   
         q->adjvex  =   i;   /* ����û���ָ��Ķ���λ�� */
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
//=                      ���ڽӱ�                                =
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
//=                      ��ӡ�ڽӱ�                              =
//================================================================
int PrintALGraph(ALGraph *G)     
{
 int i;
 struct ArcNode *p;
 char lBraket,rBraket;
 if (G->kind==UDN ||G->kind==UDG)
      {lBraket='(';rBraket=')'; }
 else {lBraket='<';rBraket='>'; }
 cout<<"��ӡ"<<((G->kind==UDG)?"����ͼ":(G->kind==UDN)?"������":(G->kind==DG)?"����ͼ":"������")<<endl;
 for(i=0 ; i <G->vexnum ; i++)
 {
  cout<<"����ţ�"<<setw(3)<<i<<"  ���ƣ�"<<G->vexs[i].data<<"  �ڽ�:";
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
 cout<<"���㹲"<<G->vexnum<<"��\t" <<"�߹�"<<G->arcnum<<"��"<<endl; 
 return OK;
}
//================================================================
//=                      �����ڽӱ�                              =
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
 cout<<"ͼ���ٳɹ�!"<<endl;  
 return OK;
}

//-------------------------------------------------------
 //                     �ؼ�·������                     - 
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
int TopologicalOrder(ALGraph G, IntStack &T) {  // �㷨7.13
  // ������G�����ڽӱ�洢�ṹ����������¼������緢��ʱ��ve(ȫ�ֱ���)��
  // TΪ�������ж���ջ��SΪ����ȶ���ջ��
  // ��G�޻�·������ջT����G��һ���������У��Һ���ֵΪOK������ΪERROR��
  IntStack S;
  int count=0,k,j;
  int indegree[40]={0};
  ArcNode *p;
  FindInDegree(G, indegree);  // �Ը����������indegree[0..vernum-1]
  for (int j=0; j<G.vexnum; ++j)     // ������ȶ���ջS
    if (indegree[j]==0) S.push(j);  // ���Ϊ0�߽�ջ
  //���������ж���ջT
  count = 0;  
  for(int i=0; i<G.vexnum; i++) ve[i] = 0;  // ��ʼ��
  while (!S.empty()) {
    j=S.top();S.pop();
	T.push(j);
	++count;       // j�Ŷ�����Tջ������
    for (p=G.vexs[j].firstarc;  p;  p=p->nextarc) {
      k = p->adjvex;            // ��j�Ŷ����ÿ���ڽӵ����ȼ�1
      if (--indegree[k] == 0) S.push(k);   // ����ȼ�Ϊ0������ջ
      if (ve[j]+p->weight> ve[k])  ve[k] = ve[j]+p->weight;
    }//for  *(p->info)=dut(<j,k>)
  }//while
  if (count<G.vexnum) return ERROR;  // ���������л�·
  else return OK;
} // TopologicalOrder

int CriticalPath(ALGraph G) {  // �㷨7.14
  // GΪ�����������G�ĸ���ؼ����
  IntStack T;
  int a,j,k,el,ee,dut;
  char tag;
  ArcNode *p;
  if (!TopologicalOrder(G, T)) return ERROR;
  for(a=0; a<G.vexnum; a++)
    vl[a] = ve[G.vexnum-1];    // ��ʼ�������¼�����ٷ���ʱ��
  while (!T.empty())       // ������������������vlֵ
    for (j=T.top(),T.pop(), p=G.vexs[j].firstarc;  p;  p=p->nextarc) {
      k=p->adjvex;  dut=p->weight;     //dut<j,k>
      if (vl[k]-dut < vl[j]) vl[j] = vl[k]-dut;
    }
  for (j=0; j<G.vexnum; ++j)            // ��ee,el�͹ؼ��
    for (p=G.vexs[j].firstarc;  p;  p=p->nextarc) {
      k=p->adjvex;dut=p->weight;   
      ee = ve[j];  el = vl[k]-dut;
      tag = (ee==el) ? '*' : ' ';
      cout<<'<'<<G.vexs[j].data<<','<<G.vexs[k].data<<"> weight:"<<dut<<" ee:"<<ee<<" el:"<<el<<' '<<tag<<endl;
    }
  return OK;
} // CriticalPath

//-------------------------------------------------------
//                     ��Դ���·��                     - 
//=------------------------------------------------------ 
int dis[MAX_VERTEXT_NUM]={0},path[MAX_VERTEXT_NUM]={0};
void ShortestPath_DIJ(MGraph G,int v0,int P[MAX_VERTEXT_NUM],int D[MAX_VERTEXT_NUM])
{ // �㷨7.15
  // ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]
  // �����Ȩ����D[v]��
  // ��P[v][w]ΪTRUE����w�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
  // final[v]ΪTRUE���ҽ���v��S,���Ѿ���ô�v0��v�����·����
  int i=0,j, v,w,min;
  bool final[MAX_VERTEXT_NUM];
  for (v=0; v<G.vexnum; ++v) {
    final[v] = FALSE;  
    D[v] = G.arcs[v0][v];
    if (D[v] < INFINITY) 
	    P[v] = v0;
    else P[v]=-1;
  }
  D[v0] = 0;  final[v0] = TRUE;        // ��ʼ����v0��������S��
  P[v0]=-1;
   //--- ��ʼ��ѭ����ÿ�����v0��ĳ��v��������·��������v��S�� ---
  for (i=1; i<G.vexnum; ++i) {         // ����G.vexnum-1������
    min = INFINITY;                    // ��ǰ��֪��v0������������
    for (w=0; w<G.vexnum; ++w)
      if (!final[w])                           // w������V-S��
        if (D[w]<min) { v = w;  min = D[w]; }  // w������v0�������
    final[v] = TRUE;                       // ��v0���������v����S��
    for (w=0; w<G.vexnum; ++w)             // ���µ�ǰ���·��������
      if (!final[w] && (min+G.arcs[v][w]<D[w])) { 
        // �޸�D[w]��P[w], w��V-S
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
  	      cout<<"���㣺"<<v0<<"�����㣺"<<v<<"��̳��ȣ�"<<start<<"  ·����"; 
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
//                    ��Դ���·������                  - 
//------------------------------------------------------- 
 CreateAdjMetrix("������7_34.txt",DN,mg);
 displayAdjMetrix(mg);
 ShortestPath_DIJ(mg,0,path,dis); 
 PrintShortestPath(mg,0,path,dis);
 destroyMGraph(&mg);  
/*
 CreateAdjList("����ͼ7_3.txt",UDG,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);
 

 CreateAdjMetrix("������7_16.txt",UDN,mg);
 displayAdjMetrix(mg);
 destroyMGraph(&mg); 
 
 CreateAdjList("������7_16.txt",UDN,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);
 */
 //-------------------------------------------------------
 //                     �ؼ�·������                     - 
 //------------------------------------------------------- 
 /*CreateAdjList("������7_29.txt",DN,alg);
 PrintALGraph(&alg);
 CriticalPath(alg);
 DestroyALGraph(&alg);
 return 0;
 */
}