#define TRUE 1
#define ERROR 0
#define OK 1
#define FALSE 0
#define OVERFLOW -2
#define INFINITY 65535 //��ʾ�����-->�ڴ�Ȩ��ͼ���õ�������
#define MAX_VERTEX_NUM 20 //ͼ����󶨵���
#define MAX_INFO 20  //ÿ����������Ϣ��󳤶�
typedef int Status;

//������������

typedef int TElemType;

//���Ľڵ����ݽṹ

typedef struct BiTNode{

	TElemType data;

	struct BiTNode *lchild;

	struct BiTNode *rchild;

}*BiTree,*Position;





//�����ϵ����

typedef int VRType;



//������Ϣ����

typedef char InfoType;



//������������

typedef int VertexType;



//ͼ������:�ֱ��������ͼ��������������ͼ��������

typedef enum {DG,DN,UDG,UDN} GraphKind;



typedef struct {

	VRType adj; //�����ϵ���ͣ�����Ȩͼ��1��0��ʾ�Ƿ����ڣ��Դ�Ȩͼ����ΪȨֵ����

	InfoType *info;	//������Ϣָ��

}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];





typedef struct {

	//��������

	VertexType vexs[MAX_VERTEX_NUM];

	//�ڽӾ���

	AdjMatrix arcs;

	//ͼ�ĵ�ǰ������

	int vexnum;

	//ͼ�Ļ���

	int arcnum;

	//ͼ������

	GraphKind kind;

}MGraph;





//������ĳԪ���Ƿ񱻷��ʹ�

int visited[MAX_VERTEX_NUM];



//����ͼ,����������ͼ����������

Status CreateGraph(MGraph *G);



//��������ͼ

Status CreateUDG(MGraph *G);



//��������ͼ

Status CreateDG(MGraph *G);



//����������

Status CreateUDN(MGraph *G);



//����������

Status CreateDN(MGraph *G);



//����ĳ������ͼ�е�λ��

int LocateVex(MGraph G,VertexType v);



//��ӡԪ��

Status PrintElem(int elem);



//������ȱ���ͼ

Status DFSTraverse(MGraph G,Status (*Visit) (VertexType));



//������ȵݹ����

void DFS(MGraph G,int i,Status (*Visit) (VertexType));



//����v��ֵ

VertexType GetVex(MGraph G,int v);



//����v�ĵ�һ���ڽӶ���

int FirstAdjVex(MGraph G,int v);



//w��v���ڽӵ㣬����v�����w����һ���ڽӵ�

int NextAdjVex(MGraph G,int v,int w);





//��������ͼ�������������ɭ�ֵĺ����ֵ�����T

void DFSForest(MGraph G,BiTree *T);



//��v��������������ȱ�����������TΪ���ڵ������

void DFSTree(MGraph G,int v,BiTree *T);





//ǰ�����������

Status PreOrderTraverse(BiTree T,Status (*visit) (TElemType elem));