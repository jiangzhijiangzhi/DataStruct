#include<iostream>
#include<fstream>
#include<vector>
#include<time.h>
#include<algorithm>
using namespace std;
 
struct CSTree
{
	int data;
	CSTree * lchild;
	CSTree * nextsibling;
};
 
void DFSTree(int v,CSTree *&p);
void DFSForest(CSTree *&root);
CSTree *root = NULL;//����ɭ��
bool *visited;
vector<vector<int>> mGraph;//ͼ�ṹ
int nodeNum;//ͼ�ж�����
int edgeNum;//ͼ�б���
 
void readGraph()
{
	fstream fin("E:\\myData\\combined.txt");//���ļ�
	fin>>nodeNum>>edgeNum;//��ȡ�������ͱ���
	mGraph.resize(nodeNum);//����ͼ�Ĵ�С
	visited = new bool[nodeNum];
	for(int i = 0; i < nodeNum; ++i)
	{
		visited[i] = false;
	}
	int num1, num2;
	while(fin>>num1>>num2)//��ȡÿһ����
	{
		mGraph[num1].push_back(num2);//�洢�ߵ���Ϣ
		mGraph[num2].push_back(num1);
	}
	fin.close();//�ر��ļ�
 
	for(int i = 0; i < nodeNum; ++i)
	{
		sort(mGraph[i].begin(),mGraph[i].end());//ͼ�нڵ���ڽӵ�����
	}
}
 
//��������ͼG�������������ɭ��
void DFSForest(CSTree *&root)
{
	CSTree *q = NULL;//ָ��ǰ�������ĸ��ڵ�
	for(int i = 0; i < nodeNum; ++i)
	{
		if(!visited[i])//��ǰ�ڵ�û�б����ʹ�
		{
			CSTree *p = new CSTree;//�������еĽڵ�
			p->data = i;
			p->lchild = NULL;
			p->nextsibling = NULL;
 
			if(root == NULL)//�����ǰɭ��Ϊ��
			{
				root = p;//��ǰ�����ɵĽڵ�Ϊɭ�ֵĸ��ڵ�
			}
			else
			{
				q->nextsibling = p;//��ǰ���ڵ�ָ��p
			}
			q = p;;
			DFSTree(i,q);//������qΪ���ڵ���������������
		}
	}
}
 
//�ӵ�v���������������ȱ���ͼ��������rootΪ������
void DFSTree(int v,CSTree *&root)
{
	visited[v] = true;//��ǰ�ڵ���Ϊ�����ʹ�
	bool first = true;//��ǰ�ڵ�ĵ�һ������
	int count = mGraph[v].size();//v���ڽӵ�ĸ���
	CSTree *q = NULL;//ָ��ǰ�ڵ�
	for(int i = 0; i < count; ++i)
	{
		int val = mGraph[v][i];
		if(!visited[val])//��ǰ�ڵ�û�б����ʹ�
		{
			visited[val] = true;//���õ�ǰ�ڵ㱻���ʹ�
			CSTree *p = new CSTree;//������һ���ڵ�
			p->data = val;
			p->lchild = NULL;
			p->nextsibling = NULL;
 
			if(first)//��ǰ�ڵ�ĵ�һ������
			{
				root->lchild = p;
				first = false;
			}
			else//��ǰ�ڵ����������
			{
				q->nextsibling = p;
			}
			q = p;
			DFSTree(val,p);
		}
	}
}
 
//��ǰ������ķ�ʽ���ɭ��
void show(CSTree *root)
{
	if(root != NULL)
	{
		cout<<root->data<<" ";
		show(root->lchild);
		show(root->nextsibling);
	}
}
 
int main(void)
{
	readGraph();
	cout<<"����ͼ�ж���ĸ�����"<<nodeNum<<endl;
	cout<<"����ͼ�бߵ�������"<<edgeNum<<endl;
	clock_t start,end;
	start = clock();
	DFSForest(root);
	end = clock();
	cout<<"����ɭ��ʱ�䣺"<<float(end - start)/CLOCKS_PER_SEC*1000<<endl;
	system("pause");
	return 0;
}