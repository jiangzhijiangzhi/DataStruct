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
	RedType r[MAXSIZE+1];//r[0]���û�����Ϊ�ڱ���Ԫ 
	int length;
}SqList;
typedef SqList HeapType;//�Ѳ���˳���洢��ʾ
void HeapAdjust(HeapType &H, int s, int m) {  // �㷨10.10
  // ��֪H.r[s..m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬
  // ����������H.r[s]�Ĺؼ��֣�ʹH.r[s..m]��Ϊһ��С����
  // �������м�¼�Ĺؼ��ֶ��ԣ�
  int j;
  RedType rc;
  rc = H.r[s];
  for (j=2*s; j<=m; j*=2) {   // ��key��С�ĺ��ӽ������ɸѡ
    if (j<m && H.r[j].key>H.r[j+1].key) ++j; // jΪkey��С�ļ�¼���±�
    if (rc.key<=H.r[j].key) break;         // rcӦ������λ��s��
    H.r[s] = H.r[j];  s = j;
  }
  H.r[s] = rc;  // ����
} // HeapAdjust
void HeapSort(HeapType &H) {  // �㷨10.11
   // ��˳���H���ж�����
   int i;
   RedType temp;
   for (i=H.length/2;i>0; --i)  // ��H.r[1..H.length]����С����
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