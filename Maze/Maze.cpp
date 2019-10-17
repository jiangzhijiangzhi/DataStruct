#include"iostream"
#include"stack"
#include"string"
#include"stdlib.h"
#include"stdio.h"
using namespace std;

bool vis[11][11];
class point{
	public:
	int x;
	int y;
	int dir;
	point(int a,int b,int d=1){
		x=a;
		y=b;
		dir=d; 
	}
	bool equal(point a){
		return x==a.x&&y==a.y;
	}
};

bool pass(int maze[][10],point pos){
	return !vis[pos.x][pos.y]&&!maze[pos.x][pos.y];
}

point next_position(point a,int dir){
	if(dir==1)return point(a.x+1,a.y);
	if(dir==2)return point(a.x,a.y+1);
	if(dir==3)return point(a.x-1,a.y);
	if(dir==4)return point(a.x,a.y-1);
}

stack<point> maze_path(int maze[][10],point start,point end){
	stack<point> path;
	point current_position=start;
	do{
		if(pass(maze,current_position)){
			vis[current_position.x][current_position.y]=true;
			point temp(current_position.x,current_position.y,1);
			path.push(temp); 
			if(current_position.equal(end))return path;
			current_position=next_position(current_position,1);
		}
		else{
			if(path.size()){
				point temp=path.top();
			path.pop();
			while(temp.dir==4&&!path.empty()){
				temp=path.top();
				vis[temp.x][temp.y]=true;
				path.pop();
			}
			if(temp.dir<4){
				temp.dir++;
				path.push(temp);
				current_position=next_position(temp,temp.dir);
			}
			}
			
		}
	}while(path.size());
	return path;
}

int main()
{
	int maze[10][10];
	FILE *mymaze;
	mymaze=freopen("F://DataStruct//Maze//mazes.txt","r",stdin);
	if(mymaze==NULL){
		printf("error on freopen");
		return 0;
	}
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			scanf("%d",&maze[i][j]);
		}
	}
	fclose(mymaze);
	cout<<"迷宫如下："<<endl;
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(maze[i][j]==1)printf("+ ");
			if(maze[i][j]==0)printf("  ");
		}
		printf("\n");
	}
	point start(1,1),end(8,8);
	stack<point> path=maze_path(maze,start,end);
	cout<<"路线如下: \n";
	while(path.size()){
		printf("(%d,%d)",path.top().x,path.top().y);
		maze[path.top().x][path.top().y]=6;
		path.pop();
	} 
	printf("\n显示如下：\n");
	for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			if(maze[i][j]==1)printf("+ ");
			if(maze[i][j]==0)printf("  ");
			if(maze[i][j]==6)printf("$ ");
		}
		printf("\n");
	}
	return 0;
} 