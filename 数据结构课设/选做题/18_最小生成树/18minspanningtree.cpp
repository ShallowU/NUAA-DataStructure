#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm> //用于sort
#include <vector>
//#include <utility> //用于pair，但vector可以包含调用
using namespace std;
#define MaxNum  1e9
#define VMax 40
// 图的储存结构，运用邻接矩阵
typedef struct test
{
    float arcs[VMax+1][VMax+1];
    int vexnum, arcnum;
    string VexName[VMax+1];
} MGraph;
struct minspanningtree
{
    int vexcode;
    float lowcost;
};
minspanningtree closest[VMax+1];
int parent[VMax + 1];

void CreateGraph(MGraph &G)
{
    int i,j;
    for (i = 0; i < VMax+1; i++)
    {
        for (j = 0; j <VMax+1; j++)
        {
            G.arcs[i][j] = MaxNum;
        }
    }
}
//*************************************************
//		 读取文件中图的信息
//*************************************************
void InputGraph(MGraph &G,fstream &infile)
{
    infile.clear();
	infile.seekg(0L,ios::beg);
    int i,j;
    string beginvex="",endvex="";
    int beginnode,endnode;
    float weight;
    cout<<"*************************************文件读取图的信息如下******************************"<<endl;
    infile>>G.vexnum;
    cout<<"vexnum:"<<G.vexnum<<endl;
    for(i=1;i<=G.vexnum;i++)
    {
        infile>>G.VexName[i];
        cout<<"vex"<<i<<":"<<G.VexName[i]<<endl;
    }
    infile>>G.arcnum;
    cout<<"arcnum:"<<G.arcnum<<endl;
    for(j=1;j<=G.arcnum;j++)
    {
        infile>>beginvex>>endvex;
        for(i=1;i<=G.vexnum;i++)
        {
            if(G.VexName[i]==beginvex)
                beginnode=i;
            if(G.VexName[i]==endvex)
                endnode=i;
        }
        infile>>weight;
        G.arcs[beginnode][endnode]=weight;
        G.arcs[endnode][beginnode]=weight;
        cout<<beginvex<<"——"<<endvex<<": "<<weight<<endl;
    }
    cout<<"*************************************文件读取图的信息如上******************************"<<endl;
}
//*************************************************
//		 prim算法求最小生成树
//*************************************************
void minspanningtree_prim(MGraph G,int v)
{
    int i,j;
    int flag;
    float weightsum=0.0;
    for(j=1;j<=G.vexnum;j++)
    {
        closest[j].lowcost=G.arcs[v][j];
        closest[j].vexcode=v;
    }
    closest[v].lowcost=0;
    for(i=2;i<=G.vexnum;i++)
    {
        float min=MaxNum;
        for(j=1;j<=G.vexnum;j++)
        {
            if(closest[j].lowcost!=0&&closest[j].lowcost<min)
            {
                min=closest[j].lowcost;
                flag=j;
            }
        }
        weightsum+=min;
        cout<<"边("<<G.VexName[closest[flag].vexcode]<<","<<G.VexName[flag]<<")"<<"的权值为："<<min<<endl;
        closest[flag].lowcost=0;
        for(j=1;j<=G.vexnum;j++)
        {
            if(G.arcs[flag][j]<closest[j].lowcost)
            {
                closest[j].lowcost=G.arcs[flag][j];
                closest[j].vexcode=flag;
            }
        }
    }
    cout<<"prim方法下从"<<G.VexName[v]<<"顶点产生最小生成树权值之和为:"<<weightsum<<endl;
}
//用于查找v的祖先判断是否为环
int find(int v)
{
    if (parent[v] == -1)
        return v;
    return find(parent[v]);
}
//设置祖先
void Union(int x, int y)
{
    int xset = find(x);
    int yset = find(y);
    parent[xset] = yset;
}
//用于sort排序方式
bool compareEdges(pair<float, pair<int, int>> a, pair<float, pair<int, int>> b)
{
    return a.first < b.first;
}
//*************************************************
//		 运用kruskal求最小生成树
//*************************************************
void minspanningtree_kruskal(MGraph G)
{
    int i, j;
    vector<pair<float, pair<int, int>>> edges;

    for (i = 1; i <= G.vexnum; i++)
    {
        for (j = i + 1; j <= G.vexnum; j++)
        {
            if (G.arcs[i][j] != MaxNum)
                edges.push_back({G.arcs[i][j], {i, j}});
        }
    }

    sort(edges.begin(), edges.end(), compareEdges);

    float weightsum = 0.0;
    //初始化parent
    for (i = 1; i <= G.vexnum; i++)
    {
        parent[i] = -1;
    }

    for (size_t i = 0; i < edges.size(); i++)
    {
        int x = find(edges[i].second.first);
        int y = find(edges[i].second.second);

        if (x != y)
        {
            cout << "边(" << G.VexName[edges[i].second.first] << ", " << G.VexName[edges[i].second.second] << ")的权值为: " << edges[i].first << endl;
            weightsum += edges[i].first;
            Union(x, y);
        }
    }

    cout << "Kruskal方法生成的最小生成树总权值为:" << weightsum << endl;
}

int main()
{
    MGraph G;
    CreateGraph(G);
    int v=1;
    fstream infile("minspanningtree.txt",ios::in);
    if(!infile)
	{
		cout <<"文件打开失败!"<<endl;
		exit(0);
	}
    InputGraph(G,infile);

    cout<<"prim方法下从"<<G.VexName[v]<<"顶点产生最小生成树如下:"<<endl;
    minspanningtree_prim(G,v);

    cout<<endl;
    cout << "Kruskal方法生成最小生成树如下:"<< endl;
    minspanningtree_kruskal(G);

    cout << endl;
    system("pause");
    return 0;
}
