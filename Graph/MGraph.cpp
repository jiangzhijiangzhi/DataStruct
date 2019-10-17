#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mgraph.h"

/*

* @description:����ͼ,��������ͼ������ͼ����������������

*/

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







/*

* @description:��������ͼ

* @more:�ּ�������

	1.ȷ��������/����

	2.ȷ�����������ֵ

	3.��ʼ���ڽӾ���

	4.ȷ���ڽӾ���

*/

Status CreateUDG(MGraph *G) {

	int i,j,k,infoflag,len;

	char c;

	//����һ���ݴ�����һ����ʱָ��

	char str[MAX_INFO];

	char *info;



	VertexType v1,v2;



	len = 0;



	//ȷ��������/����

	printf("please enter vexnum, arcnum is info(1 or 0):");

	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&infoflag);



	//ȷ�����������ֵ

	printf("the value of each vertex:");

	for(i = 0;i < (*G).vexnum ; i++)

		scanf("%d,",&(*G).vexs[i]);

	

	//��ʼ���ڽӾ���

	for(i = 0; i < (*G).vexnum; i++) 

		for(j = 0;j < (*G).vexnum ; j++) {

			(*G).arcs[i][j].adj = 0;	//����ͼ

			(*G).arcs[i][j].info = NULL;

		}





	//ȷ���ڽӾ���

	printf("please %d heads and %d tails:\n",(*G).vexnum,(*G).arcnum);

	for(k = 0; k < (*G).arcnum; k++) {

		scanf("%d,%d",&v1,&v2);

		

		i = LocateVex(*G,v1);

		j = LocateVex(*G,v2);



		if(i >= 0 && j >= 0)

			(*G).arcs[i][j].adj = (*G).arcs[j][i].adj = 1;	//����ͼ,�Գƾ���

		//��������и�����Ϣ,�����벢����ռ�

		if(infoflag) {

			printf("please enter the info:");

			while( (c = getchar()) != '#')

				str[len++] = c;



			info = (char *) malloc(len * sizeof(char));

			str[len] = '\0';



			strcpy(info,str);



			(*G).arcs[i][j].info = (*G).arcs[i][j].info = info;

		}

	}



	(*G).kind = UDG;



	return OK;

}











/*

* @description:��������ͼ

* @more:�ּ�������

	1.ȷ��������/����

	2.ȷ�����������ֵ

	3.��ʼ���ڽӾ���

	4.ȷ���ڽӾ���

*/

Status CreateDG(MGraph *G) {

	int i,j,k,len,infoflag;

	VertexType v1,v2;



	char str[MAX_INFO];

	char *info;

	char c;



	//ȷ��������/����

	printf("please enter vexnum , arcnum and is info(1 or 0):");

	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&infoflag);



	//ȷ�����������ֵ

	printf("the value of each vertex:");

	for(i = 0;i < (*G).vexnum ; i++)

		scanf("%d,",&(*G).vexs[i]);

	

	//��ʼ���ڽӾ���

	for(i = 0; i < (*G).vexnum; i++) 

		for(j = 0;j < (*G).vexnum ; j++) {

			(*G).arcs[i][j].adj = 0;	//����ͼ

			(*G).arcs[i][j].info = NULL;

		}





	//ȷ���ڽӾ���

	printf("please %d heads and %d tails:\n",(*G).vexnum,(*G).arcnum);

	for(k = 0; k < (*G).arcnum; k++) {

		scanf("%d,%d",&v1,&v2);

		

		i = LocateVex(*G,v1);

		j = LocateVex(*G,v2);



		if(i >= 0 && j >= 0)

			(*G).arcs[i][j].adj = 1;	//����ͼ



		//��������и�����Ϣ,�����벢����ռ�

		if(infoflag) {

			printf("please enter the info:");

			while( (c = getchar()) != '#')

				str[len++] = c;



			info = (char *) malloc(len * sizeof(char));

			strcpy(info,str);



			(*G).arcs[i][j].info = info;

		}

	}



	(*G).kind = DG;



	return OK;

}









/*

* @description:����������

*/



Status CreateDN(MGraph *G) {

	int i,j,k,len,infoflag,w;

	VertexType v1,v2;



	char str[MAX_INFO];

	char *info;

	char c;



	//ȷ��������/����

	printf("please enter vexnum , arcnum and is info(1 or 0):");

	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&infoflag);



	//ȷ�����������ֵ

	printf("the value of each vertex:");

	for(i = 0;i < (*G).vexnum ; i++)

		scanf("%d,",&(*G).vexs[i]);

	

	//��ʼ���ڽӾ���

	for(i = 0; i < (*G).vexnum; i++) 

		for(j = 0;j < (*G).vexnum ; j++) {

			(*G).arcs[i][j].adj = INFINITY;	//������

			(*G).arcs[i][j].info = NULL;

		}





	//ȷ���ڽӾ���

	printf("please %d heads and %d tails and weights:\n",(*G).vexnum,(*G).arcnum);

	for(k = 0; k < (*G).arcnum; k++) {

		scanf("%d,%d,%d",&v1,&v2,&w);

		

		i = LocateVex(*G,v1);

		j = LocateVex(*G,v2);



		if(i >= 0 && j >= 0)

			(*G).arcs[i][j].adj = w;	//����ͼ



		//��������и�����Ϣ,�����벢����ռ�

		if(infoflag) {

			printf("please enter the info:");

			while( (c = getchar()) != '#')

				str[len++] = c;



			info = (char *) malloc(len * sizeof(char));

			strcpy(info,str);



			(*G).arcs[i][j].info = info;

		}

	}



	(*G).kind = DN;



	return OK;

}













/*

* @description:����������

*/



Status CreateUDN(MGraph *G) {

	int i,j,k,len,infoflag,w;

	VertexType v1,v2;



	char str[MAX_INFO];

	char *info;

	char c;



	//ȷ��������/����

	printf("please enter vexnum , arcnum and is info(1 or 0):");

	scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&infoflag);



	//ȷ�����������ֵ

	printf("the value of each vertex:");

	for(i = 0;i < (*G).vexnum ; i++)

		scanf("%d,",&(*G).vexs[i]);

	

	//��ʼ���ڽӾ���

	for(i = 0; i < (*G).vexnum; i++) 

		for(j = 0;j < (*G).vexnum ; j++) {

			(*G).arcs[i][j].adj = INFINITY;	//������

			(*G).arcs[i][j].info = NULL;

		}





	//ȷ���ڽӾ���

	printf("please enter heads,tails and weights:\n",(*G).vexnum,(*G).arcnum);

	for(k = 0; k < (*G).arcnum; k++) {

		scanf("%d,%d,%d",&v1,&v2,&w);

		

		i = LocateVex(*G,v1);

		j = LocateVex(*G,v2);



		if(i >= 0 && j >= 0)

			(*G).arcs[i][j].adj = (*G).arcs[j][i].adj = w;	//������



		//��������и�����Ϣ,�����벢����ռ�

		if(infoflag) {

			printf("please enter the info:");

			while( (c = getchar()) != '#')

				str[len++] = c;



			info = (char *) malloc(len * sizeof(char));

			strcpy(info,str);



			(*G).arcs[i][j].info = info;

		}

	}



	(*G).kind = UDN;



	return OK;

}















/*

* @description:�ж�ͼ���Ƿ����v���㣬�����򷵻ظö�����ͼ�е�λ�ã����򷵻�������Ϣ

*/

int LocateVex(MGraph G,VertexType v) {

	int i;



	for(i = 0;i < G.vexnum; i++)

		//ƥ���򷵻�

		if(G.vexs[i] == v)

			return i;



	return -1;

}





/*

* @description:������ȱ���ͼ

* @more:��Ϊ����

	1.һ��Ҫ���³�ʼ�����ʼ�¼����

	2.����û�з��ʹ��Ķ��㣬�����·��ʼ�¼����

* @�������еĵڶ���ѭ����Ҫ��Ϊ�˱�֤ÿ�����㶼�ܱ����ʵ�

   ��DFS�е�ѭ������Ѱ�ҵ�ǰ�ڵ�����ڽڵ�������

   �ؼ��Ĺؼ����ڵݹ�����-->�ϻ�

*/

Status DFSTraverse(MGraph G,Status (*Visit) (VertexType)) {

	int i;

	//��ʼ�����ʼ�¼����

	for(i = 0;i < G.vexnum; i++)

		visited[i] = FALSE;

	

	for(i = 0;i < G.vexnum ; i++) 

		if(!visited[i])

			DFS(G,i,Visit);



	return OK;

}







/*

* @description:������ȵݹ����

*/

void DFS(MGraph G,int i,Status (*Visit) (VertexType)) {

	int j,w;



	//���

	visited[i] = TRUE;

	Visit(G.vexs[i]);



	for(w = FirstAdjVex(G,i); w >= 0; w = NextAdjVex(G,i,w))

		if(!visited[w])

			DFS(G,w,Visit);

}







/*

* @description:����v��ֵ

*/

VertexType GetVex(MGraph G,int v) {

	if(v >= G.vexnum || v < 0)

		exit(ERROR);



	return G.vexs[v];

}







/*

* @description:����v(���)�ĵ�һ�����ڽڵ㣨��ţ�

*/

int FirstAdjVex(MGraph G,int v) {

	if(v > G.vexnum || v < 0)

		return -1;

	

	int i,j;



	j = 0;



	//�������

	if(G.kind == DN || G.kind == UDN )

		j = INFINITY;



	for(i = 0;i < G.vexnum; i++) 

		if(G.arcs[v][i].adj != j)

			return  i;



	return -1;

}



/*

* @description:w��v�����ڽڵ㣬����v���w����һ���ڵ����ţ����򷵻�-1

*/

int NextAdjVex(MGraph G,int v,int w) {

	int i,j;

	

	j = 0;

	//���Ϊ��

	if(G.kind == DN || G.kind == UDN)

		j = INFINITY;

	//�����㲻����

	if(G.arcs[v][w].adj == j)

		return -1;

	//��w֮��Ľڵ㿪ʼ�Ϳ���

	for(i = w + 1; i < G.vexnum; i++) 

		if(G.arcs[v][i].adj != j)

			return i;



	return -1;

}







/*

* @description:��ӡԪ��

*/

Status PrintElem(int elem) {

	printf("%d\t",elem);

	return OK;

}









/*

* @description:��������ͼ�������������ɭ�ֵĺ����ֵ�����T

*/

void DFSForest(MGraph G,BiTree *T) {

	int i;

	BiTree p,q;



	

	*T = p = q = NULL;



	for(i = 0; i < G.vexnum; i++) 

		visited[i] = FALSE;

	

	for(i = 0; i < G.vexnum; i++) {

		if(!visited[i]) {

			p = (BiTree) malloc(sizeof(struct BiTNode));

			if(!p)

				exit(OVERFLOW);



			p->data = GetVex(G,i);

			p->rchild = NULL;

			p->lchild = NULL;



			//��һ���������ĸ�

			if(!(*T)) 

				*T = p;

			//�����������ĸ�����һ�������ֵ�

			else

				q->rchild = p;

			q = p;	//qָʾ��ǰ�������ĸ�



			DFSTree(G,i,&p);

				

		}

	}



}





/*

* @description:��v��������������ȱ�����������TΪ���ڵ��������

*/

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







/*

* @description:ǰ�����������

*/

Status PreOrderTraverse(BiTree T,Status (*visit) (TElemType elem)) {

	if(T) {

		if(visit(T->data))

			if(PreOrderTraverse(T->lchild,visit))

				if(PreOrderTraverse(T->rchild,visit))

					return OK;

		return ERROR;

	}

	

	return OK;

}