#include <stdio.h>
#include "iostream"
#include "iomanip"
#include "stdlib.h"
#include <time.h>
#include <string.h>
#define MAXSIZE 100005 
using namespace std;
typedef int KeyType;
typedef char InfoType;
typedef struct{
	KeyType key;
	InfoType otherinfo;
}RedType;
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或者作为哨兵单元 
	int length;
}SqList;
typedef SqList HeapType;//堆采用顺序表存储表示
void HeapAdjust(HeapType &H, int s, int m) {  // 算法10.10
  // 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，
  // 本函数调整H.r[s]的关键字，使H.r[s..m]成为一个小顶堆
  // （对其中记录的关键字而言）
  int j;
  RedType rc;
  rc = H.r[s];
  for (j=2*s; j<=m; j*=2) {   // 沿key较小的孩子结点向下筛选
    if (j<m && H.r[j].key>H.r[j+1].key) ++j; // j为key较小的记录的下标
    if (rc.key<=H.r[j].key) break;         // rc应插入在位置s上
    H.r[s] = H.r[j];  s = j;
  }
  H.r[s] = rc;  // 插入
} // HeapAdjust
void HeapSort(HeapType &H) {  // 算法10.11
   // 对顺序表H进行堆排序。
   int i;
   RedType temp;
   for (i=H.length/2;i>0; --i)  // 把H.r[1..H.length]建成小顶堆
      HeapAdjust ( H, i, H.length );
} // HeapSort

int main()
{
	int n,m,i,elem,top=1;HeapType H;char a[10];
	while(scanf("%d %d",&n,&m)!=EOF)
	{H.length=n;
	for(i=1;i<=n;i++)
	scanf("%d ",&H.r[i].key);
	while(m--)
	{
		scanf("%s",a);
		if(a[1]=='o') {	
		HeapSort(H);printf("%d\n",H.r[1].key);H.length--;
		for(int i=1;i<=H.length;i++)
	H.r[i].key=H.r[i+1].key;}
		else{
			scanf("%d",&elem);
			H.length++;
			H.r[H.length].key=elem;
			HeapSort(H);
		}
	}
	return 0;
	}
}