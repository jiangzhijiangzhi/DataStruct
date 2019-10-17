#include <stdio.h>
#include<stdarg.h>
#include<string.h>
#define MAXSIZE 30
#define ERROR 0
#define OK 1
typedef struct{
	int i;
	int j;
	int e;
} Triple;
typedef struct {
	Triple data[MAXSIZE+1];
	int rpos[MAXSIZE+1];
	int mu,nu,tu;
}RLSMatrix;
RLSMatrix M={{{},{1,1,3},{1,4,5},{2,2,-1},{3,1,2}},{},3,4,4};
RLSMatrix N={{{},{1,2,2},{2,1,1},{3,1,-2},{3,2,4}},{},4,2,4};
RLSMatrix Q={{},{},3,2,0};
int mults(RLSMatrix M,RLSMatrix N,RLSMatrix &Q)
{
	int arow,tp,p,q,t,ccol,brow;
	int ctemp[30];
	if(M.nu!=N.mu) return ERROR;
	Q.mu=M.mu;Q.nu=N.nu;Q.tu=0;
	if(M.tu*N.tu!=0)
	{
		for(arow=1;arow<=M.mu;++arow)
		{
			ctemp[arow]=0;
			Q.rpos[arow]=Q.tu+1;
			if(arow<M.mu)tp=M.rpos[arow+1];
			else{tp=M.tu+1;}
			for(p=M.rpos[arow];p<tp;++p)
			{
				brow=M.data[arow].j;
				if(brow<N.mu) t=N.rpos[brow+1];
				else{t=N.tu+1;}
				for(q=N.rpos[brow];q<t;++q)
				{
					ccol=N.data[q].j;
					ctemp[ccol]+=M.data[p].e*N.data[p].e; 
				}
			}
			for(ccol=1;ccol<=Q.nu;++ccol)
			if(ctemp[ccol]){
				if(++Q.tu>MAXSIZE)return ERROR;
				Q.data[Q.tu].i=arow;  
				Q.data[Q.tu].j=ccol;  
				Q.data[Q.tu].e=ctemp[ccol];
			}
		}
	}
	return OK;
} 
void print(RLSMatrix M)
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
	mults(M,N,Q);
	print(Q);
}
