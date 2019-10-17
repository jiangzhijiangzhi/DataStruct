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

typedef enum {UDG=0,UDN=1,DG=2,DN=3} GraphKind;//����ͼ��������������ͼ�������� 
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
 //������Ϣ����
 while (gets(buff))
   {if(!(strchr(buff,lBraket)||strchr(buff,',')))
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
    else if (kd==DN)
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
   {if(!(strchr(buff,lBraket)||strchr(buff,',')))
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

int main()
{
 MGraph mg;
 ALGraph alg;
/*
 CreateAdjMetrix("����ͼ7_3.txt",UDG,mg);
 displayAdjMetrix(mg);
 destroyMGraph(&mg);  

 CreateAdjList("����ͼ7_3.txt",UDG,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);
 */

 CreateAdjMetrix("������7_16.txt",UDN,mg);
 displayAdjMetrix(mg);
 destroyMGraph(&mg); 
 
 CreateAdjList("������7_16.txt",UDN,alg);
 PrintALGraph(&alg);
 DestroyALGraph(&alg);

 return 0;
}