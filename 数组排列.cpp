#include<stdio.h>
#include<iostream>
using namespace std;
void sort(int *a,int len){
	int i;
        int dataLen = 1;
        for(int j=len-1; j>=0; j--)
                if(a[j] < 0)
                {
                        i = j;
                        break;
                }
 
        while(i > 0)
        {
                while(i>0 && a[i-1] < 0)
                {
                        i--;
                        dataLen++;
                }
                if(i == 0)
                        break; //�������ǰ�涼�Ǹ�������ô�Ѿ��ź��ˣ�ֱ�ӷ���
                int temp = a[i-1];
                memcpy(&a[i-1], &a[i], dataLen*sizeof(int));//����ע��memcpy�Ĳ�����λΪ�ֽ�
                a[i+dataLen-1] = temp;
                i--;
        }
}
int main(){
	int a[]={1,-4,5,9,-8,-1};
	int len=6;
	for(int i=0;i<len;i++){
		printf("%d",a[i]);
		}
	printf("\n");
	sort(a,len);
	for(int i=0;i<len;i++){
		printf("%d",a[i]);
	}
	printf("\n");
	return 0;
}
