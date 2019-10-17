#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>
#define NUM 20
using namespace std;
struct Info{
    int num;
    int value;
    Info(){}
    Info(int x,int y):num(x),value(y){}//���캯��
};
int indree[NUM]={0};
int N,M;//��ʾ�������ͱ�����
vector<list<Info> > Graph(NUM);
stack<int> T;//����������������Ķ��㣬�����������;
int Ve[NUM];
int Vl[NUM];
    //������������¼� �����緢��ʱ��Ve(j)����ٷ���ʱ��Vl(j)��
bool tuopsort(){
    int count = 0;
    stack<int> q;
    memset(Ve, 0, sizeof(Ve));
    for(int i = 1;i<=N;i++)
        if(!indree[i])
            q.push(i);
    while(!q.empty()){
        int t = q.top();
        q.pop();
        count++;
        T.push(t);
        for(list<Info>::iterator it =  Graph[t].begin(); it!=Graph[t].end();it++){
            int k = it->num;
            if(!(--indree[k]))
                q.push(k);
            Ve[k] = max(Ve[k],Ve[t]+it->value);//���ϸ�����������ֵ��
        }
    }
    if(count<N)
        return false;
    else
        return true;
}
bool CritPath(){
    if(!tuopsort()) return false;
    memset(Vl, 125, sizeof(Vl));
    Vl[N] = Ve[N];
    while(!T.empty()){
        int t = T.top();
        T.pop();
        for(list<Info>::iterator it =  Graph[t].begin(); it!=Graph[t].end();it++){
            int k = it->num;
            Vl[t] = min(Vl[t],Vl[k]-it->value);//Ҳ�ǲ��ϵĸ��£�
       }
    }

    for(int i = 1;i<=N;i++){

        cout <<Ve[i]<<"   "<<Vl[i]<<endl;

    }
    int ee,el;
    for(int i = 1;i<=N;i++){
        for(list<Info>::iterator it =  Graph[i].begin(); it!=Graph[i].end();it++){
            int k = it->num;
            ee= Ve[i];
            el = Vl[k]-it->value;
            int flag = (ee==el)?1:0;

            cout <<i<<"v->v"<<k<<" "<<it->value<<" "<<ee<<" "<<el<<" "<<flag<<endl;
        }
    }
    return true;
}
void print(Info f){
    cout <<f.num<<"V-"<<f.value<<" ";
}
int main(){
    cin>>N>>M;
    for(int i=1;i<=M;i++){
        int v,f,e;
        cin>>v>>f>>e;
        if(f!=e)
            {Graph[f].push_front(Info(e,v));indree[e]++;}
    }
    cout <<"ͼ���ڽӱ��棺"<<endl;

     for(int i= 1;i<=N;i++){
        cout <<i<<"   ";
        for_each(Graph[i].begin(),Graph[i].end() , print);
        cout <<endl;
    }

     cout <<"ÿһ���������ȣ�";
     for(int i = 1;i<=N;i++)
     cout <<indree[i]<<" ";
   	cout <<endl;

    CritPath();
    return 0;
}
