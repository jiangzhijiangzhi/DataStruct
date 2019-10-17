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
CSTree *root = NULL;//生成森林
bool *visited;
vector<vector<int>> mGraph;//图结构
int nodeNum;//图中顶点数
int edgeNum;//图中边数
 
void readGraph()
{
	fstream fin("E:\\myData\\combined.txt");//打开文件
	fin>>nodeNum>>edgeNum;//读取顶点数和边数
	mGraph.resize(nodeNum);//设置图的大小
	visited = new bool[nodeNum];
	for(int i = 0; i < nodeNum; ++i)
	{
		visited[i] = false;
	}
	int num1, num2;
	while(fin>>num1>>num2)//读取每一条边
	{
		mGraph[num1].push_back(num2);//存储边的信息
		mGraph[num2].push_back(num1);
	}
	fin.close();//关闭文件
 
	for(int i = 0; i < nodeNum; ++i)
	{
		sort(mGraph[i].begin(),mGraph[i].end());//图中节点的邻接点排序
	}
}
 
//建立无向图G的深度优先生成森林
void DFSForest(CSTree *&root)
{
	CSTree *q = NULL;//指向当前生成树的根节点
	for(int i = 0; i < nodeNum; ++i)
	{
		if(!visited[i])//当前节点没有被访问过
		{
			CSTree *p = new CSTree;//创建树中的节点
			p->data = i;
			p->lchild = NULL;
			p->nextsibling = NULL;
 
			if(root == NULL)//如果当前森林为空
			{
				root = p;//当前新生成的节点为森林的根节点
			}
			else
			{
				q->nextsibling = p;//当前根节点指向p
			}
			q = p;;
			DFSTree(i,q);//生成以q为根节点的深度优先生成树
		}
	}
}
 
//从第v个顶点出发深度优先遍历图，建立以root为根的树
void DFSTree(int v,CSTree *&root)
{
	visited[v] = true;//当前节点标记为被访问过
	bool first = true;//当前节点的第一个孩子
	int count = mGraph[v].size();//v的邻接点的个数
	CSTree *q = NULL;//指向当前节点
	for(int i = 0; i < count; ++i)
	{
		int val = mGraph[v][i];
		if(!visited[val])//当前节点没有被访问过
		{
			visited[val] = true;//设置当前节点被访问过
			CSTree *p = new CSTree;//新生成一个节点
			p->data = val;
			p->lchild = NULL;
			p->nextsibling = NULL;
 
			if(first)//当前节点的第一个孩子
			{
				root->lchild = p;
				first = false;
			}
			else//当前节点的其他孩子
			{
				q->nextsibling = p;
			}
			q = p;
			DFSTree(val,p);
		}
	}
}
 
//以前序遍历的方式输出森林
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
	cout<<"无向图中顶点的个数："<<nodeNum<<endl;
	cout<<"无向图中边的条数："<<edgeNum<<endl;
	clock_t start,end;
	start = clock();
	DFSForest(root);
	end = clock();
	cout<<"生成森林时间："<<float(end - start)/CLOCKS_PER_SEC*1000<<endl;
	system("pause");
	return 0;
}