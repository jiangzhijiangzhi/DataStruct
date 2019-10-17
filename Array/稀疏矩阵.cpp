#include<iostream>
#include<stdlib.h>
#include<time.h>
#define MU 5
#define NU 6
#define Status int
#define ElemType int
#define ERROR 0
#define OK 1
#define MAXSIZE 12500
using namespace std;
typedef struct {
	int i, j;
	ElemType e;
}Triple;
typedef struct {
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;
Status CreateMatrix(TSMatrix &M) {
	int e, i, j, k = 1;
	M.mu = MU;
	M.nu = NU;
	srand((unsigned)time(NULL));
	M.tu = rand() % 15;
	for(i=1;i<M.mu;i++)
		for (j = 1; j < M.nu; j++)
		{
			e = rand() % 30;
			if (e != 0) {
				M.data[k].i = i;
				M.data[k].j = j;
				M.data[k].e = e;
				k++;
				if (k == M.tu)
					break;
			}
		}
	return OK;
}
void print(TSMatrix M)
{
	int k;
	printf("mu=%-2d, nu=%-2d, tu=%-2d", M.mu, M.nu, M.tu);
	printf("\n");
	for (k = 1; k <= M.tu; k++)
	{
		printf("i=%-2d, j=%-2d, e=%-2d", M.data[k].i, M.data[k].j, M.data[k].e);
		printf("\n");
	}
}
int main()
{
	TSMatrix M, T,R;
	CreateMatrix(M);
	printf("Ï¡Êè¾ØÕóM£º\n");
	print(M);
	system("pause");
	return 0;
}
