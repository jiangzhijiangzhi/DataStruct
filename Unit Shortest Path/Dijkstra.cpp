#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;

const int maxn=10000;
int dir[201];
bool vis[201];
int map[201][201];
int  n,m ;
int a,b ,c ;
void dijksta(int v)
{
    int u;
    int temp;
    for (int i=0;i<n;i++)
        dir[i]=map[v][i];
    dir[v]=0;
    vis[v]=1;
    for (int i=0;i<n;i++)
    {
        temp=maxn;  //赋值要在for循环里面 这是因为每次进入的时候都需要进行比较~
        u=v;
        for (int j=0;j<n;j++)
        {
            if (!vis[j]&&temp>dir[j])
            {
                temp=dir[j];
                u=j;
            }
        }
        vis[u]=1;
        for (int j=0;j<n;j++)
        {
            if (!vis[j]&&dir[j]>dir[u]+map[u][j])
                dir[j]=dir[u]+map[u][j];
        }
    }
}
int main()
{
    int s,e;
    while (cin>>n>>m)
    {
        for (int i = 0 ; i <n ; i++)
        {
            for (int j=0 ; j <n; j++)
                map[i][j] = maxn;
        }
        for (int i=0;i<m;i++)
        {
            cin>>a>>b>>c;
            if (map[a][b]>c) map[a][b] = map[b][a] = c;
        }
        	memset(vis,0,sizeof(vis));
        cin>>s>>e;
        dijksta(s);
        if (dir[e]<maxn)
            cout<<dir[e]<<endl;
        else 
		cout<<"-1"<<endl;
    }
    return 0;
}
