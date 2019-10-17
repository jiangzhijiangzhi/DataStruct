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
                        break; //如果到最前面都是负数，那么已经排好了，直接返回
                int temp = a[i-1];
                memcpy(&a[i-1], &a[i], dataLen*sizeof(int));//这里注意memcpy的操作单位为字节
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
