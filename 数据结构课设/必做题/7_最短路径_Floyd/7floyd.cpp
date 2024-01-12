#include <iostream>
using namespace std;
#define MaxNum  1e9
#define VMax 100

typedef struct test // 图的结构
{
    int arcs[VMax][VMax];
    int vexnum, arcnum;
} MGraph;
//*************************************************
//		 建立图
//*************************************************
void CreateGraph(MGraph &G)
{
    cout << "请输入顶点数和边数：";
    cin >> G.vexnum >> G.arcnum;
    if(G.vexnum>15000||G.arcnum>1000)
    {
        throw "vexnum>15000 or arcnum>1000";
        exit(1);
    }
    int i, j;
    for (i = 0; i < G.vexnum; i++) // 初始化每条边都不相连
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = MaxNum;
        }
    }
    for (i = 0; i < G.vexnum; i++) // 顶点自身到自身边为0
    {
        G.arcs[i][i]=0;
    }
    int beginnode = 0, endnode = 0, weight = 0;
    cout << "请输入边的起点、终点以及权值：" << endl;
    int k = 0;
    for (k = 0; k < G.arcnum; k++) // 为无向图
    {
        cin >> beginnode >> endnode >> weight;
        G.arcs[beginnode][endnode] = weight;
        G.arcs[endnode][beginnode] = weight;
    }
}
//*************************************************
//		 floyd算法，算每个顶点到其余所有顶点的权值之和
//*************************************************
void Floyd(MGraph G,int &centerpoint,int &minpathsum)
{
    int D[VMax][VMax]; // D[i][j]即i到j的最短路径权值
    int path[VMax][VMax]; // path[i][j]即i到j要经过的点
    int WeightSum[VMax];  // 即每个点到其余所有顶点的权值之和
    int minIndex=-1;
    int minWeightSum=MaxNum;
    int i=0,j=0,k=0;
    for (i = 0; i < G.vexnum; i++) // 初始化辅助数组
    {
        for (j = 0; j < G.vexnum; j++)
        {
            D[i][j]=G.arcs[i][j];
            if(D[i][j]<MaxNum)
                path[i][j]=i;
            else
                path[i][j]=-1;
        }
    }
    for(k=0;k<G.vexnum;k++)
    {
        for (i = 0; i < G.vexnum; i++)
        {
            for (j = 0; j < G.vexnum; j++)
            {
                
                if(D[i][j]>D[i][k]+D[k][j]) // 若经过k以后i到j的权值更小，则更新
                {   
                    D[i][j]=D[i][k]+D[k][j];
                    path[i][j]=k;
                }
                
            }
        }
    }

    for (i = 0; i < G.vexnum; i++)
    {
        for (j = 0; j < G.vexnum; j++)
        {
            WeightSum[i]+=D[i][j];
        }
    }

    for (i = 0; i < G.vexnum; i++)
    {
        if(minWeightSum>WeightSum[i])
        {
            minWeightSum=WeightSum[i];
            minIndex=i;
        }
    }
    centerpoint=minIndex;
    minpathsum=minWeightSum;
}

int main()
{
    MGraph G;
    CreateGraph(G);
    int centerpoint,minpathsum;
    Floyd(G,centerpoint,minpathsum);
    cout<<"中心顶点编号、最小总路径分别为："<<centerpoint<<" "<<minpathsum<<endl;

    cout << endl;
    system("pause");
    return 0;
}