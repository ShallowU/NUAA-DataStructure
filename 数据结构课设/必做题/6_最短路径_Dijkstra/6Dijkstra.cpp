#include <iostream>
using namespace std;
#define MaxNum  1e9
#define VMax 100

typedef struct test // 图的邻接矩阵结构
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
    if(G.vexnum>15000||G.arcnum>1000) // 不要超出界限
    {
        throw "vexnum>15000 or arcnum>1000";
        exit(1);
    }
    int i, j;
    for (i = 0; i < G.vexnum; i++)   // 初始化空的边
    {
        for (j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = MaxNum;
        }
    }
    int beginnode = 0, endnode = 0, weight = 0;
    cout << "请输入边的起点、终点以及权值：" << endl;
    int k = 0;
    for (k = 0; k < G.arcnum; k++)
    {
        cin >> beginnode >> endnode >> weight;
        G.arcs[beginnode][endnode] = weight;
    }
}
//*************************************************
//		 在dist[]求最小值的下标
//*************************************************
int MinIndex(int dist[], int flag[], int n)
{
    int minIndex = -1;
    int minValue = MaxNum;

    for (int i = 0; i < n; i++)
    {
        if (flag[i] == 0 && dist[i] < minValue) //前提的是flag[i] == 0
        {
            minValue = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}
//*************************************************
//		 递归打印以0开始到各个顶点的路径
//*************************************************
void PrintShortestPath(int path[], int v, int s)
{
    if (v == -1)
    {
        //cout << "无路径到达" << v;
        return;
    }
    if (v == s)
    {
        cout << s;
        return;
    }

    PrintShortestPath(path, path[v], s);
    cout << "->" << v;
}
//*************************************************
//		 运用Dijkstra求最短路径
//*************************************************
void Dijkstra(MGraph G, int s)
{   //numVertices[VMax]用于保存每条路径节点数，如果权值相同该路径就立即更新
    int dist[VMax], path[VMax], flag[VMax], numVertices[VMax];
    int i = 0, j = 0;
    for (i = 0; i < G.vexnum; i++)
    {
        flag[i] = 0;
        dist[i] = G.arcs[s][i];
        if (dist[i] < MaxNum)
        {
            path[i] = s;
            numVertices[i] = 2; // 从s出发到i若存在路径，则表明此时该路径已经有s和i两个节点
        }
        else
        {
            path[i] = -1;
            numVertices[i] = MaxNum; // 两点之间没有边则路径中间节点数表示为无穷大
        }
    }
    flag[s] = 1; // 将起始点标记为被选中状态
    for (i = 0; i < G.vexnum - 1; i++) //循环选中剩余的顶点
    {
        int k;
        k = MinIndex(dist, flag, G.vexnum);
        flag[k] = 1;
        int mindist = dist[k];
        if (mindist < MaxNum)
        {
            for (j = 0; j < G.vexnum; j++) //用本轮选中的k更新s到其他顶点最短路径
            {
                if (flag[j] == 0 && dist[j] > mindist + G.arcs[k][j])
                {
                    dist[j] = mindist + G.arcs[k][j];
                    path[j] = k;
                    numVertices[j] = numVertices[k] + 1;//更新j的路径节点数为k路径的再加一
                }
                else if (flag[j] == 0 && dist[j] == mindist + G.arcs[k][j])//权值相同，则更新为节点数最少的
                {
                    int tempNumVertices = numVertices[k] + 1;
                    if (tempNumVertices < numVertices[j])
                    {
                        path[j] = k;
                        numVertices[j] = tempNumVertices;
                    }
                }
            }
        }
    }
    for (i = 1; i < G.vexnum; i++)
    {
        cout << "从0到" << i << "的最短路径为：";
        PrintShortestPath(path, i, 0);
        cout << endl;
    }
}

int main()
{
    MGraph G;
    CreateGraph(G);
    int s = 0; //设起始点为0
    Dijkstra(G, s);

    cout << endl;
    system("pause");
    return 0;
}
