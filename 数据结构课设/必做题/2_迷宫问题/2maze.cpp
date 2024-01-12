#include<iostream>
#include<fstream>
#include <stdlib.h>
#include<math.h>
#include<iomanip>
using namespace std;
#define MaxsizeStack 2000
#define MaxsizeMaze 2000
#define row 30
#define column 30
//****************************************
//				定义结构体 
//****************************************
typedef struct point{
	int x,y;	//x横坐标,y纵坐标(从0开始) 
}Point;		//定位点的结构体 

typedef struct stack{
	Point *top,*base;	//栈的栈顶和栈底指针 
}Stack;		//栈的结构体 

//****************************************
//			函数体声明 
//****************************************
bool Clearance(int *maze,Point start,Point end,Stack &S);	//通关迷宫 
void InputMaze(int *maze,fstream &infile);		//输入迷宫地图 
void GoNext(Point now,Point &next,int direct);	//移动人物位置 

void InitStack(Stack &S);			//栈初始化 
bool Pop(Stack &S,Point &out);		//弹栈 
void Push(Stack &S,Point in);		//压栈 
bool Gettop(Stack &S,Point &out);	//获取栈顶元素 

//*****************************************
//				主函数 
//*****************************************
int main()
{
	fstream infile("maze.txt",ios::in);
	if(!infile)
	{
		cout <<"文件打开失败!"<<endl;
		exit(1);
	}
	int maze[MaxsizeMaze]={0};				//存储迷宫信息 
	InputMaze(maze,infile);
	cout << "***************************************->迷宫游戏<-*******************************************" << endl;
	cout <<"    1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30"<<endl;
	cout <<"   _________________________________________________________________________________________"<<endl; 
	for(int i=1;i<=row;i++)			//输出迷宫地图 
	{
		cout <<setw(2)<<i<<"|";
		for(int j=1;j<=column;j++)
			cout <<setw(2)<<maze[i*30+j]<<" ";
		cout <<endl;
	}
	Point start,end;				//起点,终点
	bool flag=false;
	Stack S;
	InitStack(S);
	
	cout <<"请输入起点(中间用空格隔开,先行后列):";
	cin >>start.y>>start.x;
	cout <<"请输入终点(中间用空格隔开,先行后列):";
	cin >>end.y>>end.x; 
	if(maze[start.y*30+start.x]==0)
		cout <<"起点位置不合理!"<<endl;
	else if(maze[end.y*30+end.x]==0)
		cout <<"终点位置不合理!"<<endl;
	else
		flag=Clearance(maze,start,end,S);
	if(flag)
		cout <<"通关了!"<<endl;
	else
		cout <<"貌似无法通关..."<<endl;
	
	delete [] S.base;
	infile.close();
	system("pause");
	return 0;
}

//*******************************************
//				定义子函数 
//*******************************************
bool Clearance(int *maze,Point start,Point end,Stack &S)	//通关迷宫
{
	if(start.x==end.x&&start.y==end.y)		//成功走到终点 
	{
		cout <<"最终路线为:"<<endl; 
		Point *pb=S.base;
		while(pb<S.top)						//从栈底到栈顶依次输出通关路径 
		{
			cout <<"("<<pb->y<<","<<pb->x<<")->";
			pb++;
		}
		cout <<"("<<end.y<<","<<end.x<<")"<<endl;
		return true;
	}
	int left=0,right=1,up=2,down=3;			//各个方位在判断方向数组中的位置 
	bool direction[4]={true,true,true,true},repeat=false;
	//direction数组判断每个方位是否可以移动		repeat判断是否出现重复移动 
	int order[4]={1,2,3,0};				//给每个方位优先级排序,默认优先向右 
	if(end.x<start.x)		//优先向左移动 
	{
		order[0]=left;
		order[3]=right;
	}
	else if(end.x==start.x) 
	{
		if(end.y<start.y)	//优先向下移动 
		{
			order[0]=down;
			order[2]=right;
		}
		else				//优先向上移动 
		{
			order[0]=up;
			order[1]=right;
		}
	}
	Point out,next;
	if(Gettop(S,out))		//查看上一步移动,确保这一步不返回上一步 
	{
		if(out.x>start.x) direction[right]=false; 
		else if(out.x<start.x) direction[left]=false;
		else if(out.y>start.y) direction[up]=false;
		else direction[down]=false;
	}
	if(start.x==30||maze[(start.y)*30+start.x+1]==0)//走到地图右尽头或右边是墙壁 
		direction[right]=false;
	if(start.x==1||maze[(start.y)*30+start.x-1]==0)	//走到地图左尽头或左边是墙壁 
		direction[left]=false;
	if(start.y==30||maze[(start.y+1)*30+start.x]==0)//走到地图上尽头或上面是墙壁 
		direction[up]=false;
	if(start.y==1||maze[(start.y-1)*30+start.x]==0)	//走到地图下尽头或下面是墙壁 
		direction[down]=false;
	while(direction[0]||direction[1]||direction[2]||direction[3])//有方向可以移动 
	{
		if(direction[order[0]])
		{
			direction[order[0]]=false;
			GoNext(start,next,order[0]);
		}
		else if(direction[order[1]])
		{
			direction[order[1]]=false;
			GoNext(start,next,order[1]);
		}
		else if(direction[order[2]])
		{
			direction[order[2]]=false;
			GoNext(start,next,order[2]);
		}
		else
		{
			direction[order[3]]=false;
			GoNext(start,next,order[3]);
		}
		repeat=false;
		Point *pb=S.base;
		while(pb<S.top)				//判断是否走到了之前的某一步 
		{
			if(pb->x==next.x&&pb->y==next.y)
			{
				repeat=true;
				break;
			}
			pb++;
		}
		if(repeat)	continue;		//走到重复路径,换一种移动方式 
		Push(S,start);				//记录此次移动方式 
		bool flag=Clearance(maze,next,end,S);	//进入下一步移动 
		if(flag) return true;		//通关了 
	}
	Pop(S,out);						//撤回上一步移动 
	return false;
}

void InputMaze(int *maze,fstream &infile)	//输入迷宫地图 
{
	infile.clear();
	infile.seekg(0L,ios::beg);
	int count=31,x=0;
	while(!infile.eof())
	{
		infile >>x;
		if(infile.fail())
			break;
		maze[count]=x;
		count++;
	}
}

void GoNext(Point now,Point &next,int direct)	//移动人物位置 
{
	if(direct==0)			//左移 
	{
		next.x=now.x-1;
		next.y=now.y;
	}
	else if(direct==1)		//右移 
	{
		next.x=now.x+1;
		next.y=now.y;
	}
	else if(direct==2)		//上移 
	{
		next.y=now.y+1;
		next.x=now.x;
	}
	else					//下移 
	{
		next.y=now.y-1;
		next.x=now.x;
	}
}

void InitStack(Stack &S)	//初始化栈 
{
	S.base=new Point[MaxsizeStack];
	if(S.base==NULL) exit(2);
	S.top=S.base;
}

void Push(Stack &S,Point in)	//压栈 
{
	S.top->x=in.x;
	S.top->y=in.y;
	S.top++;
}

bool Pop(Stack &S,Point &out)	//弹栈 
{
	if(S.base==S.top) return false;
	S.top--;
	out.x=S.top->x;
	out.y=S.top->y;
	return true;
}

bool Gettop(Stack &S,Point &out)	//获取栈顶元素 
{
	if(S.base==S.top) return false;
	out.x=(S.top-1)->x;
	out.y=(S.top-1)->y;
	return true;
}
