#include <iostream>
// vector比使用二维数组存储树更加方便
// vector更方便用栈操作
#include <vector>

using namespace std;
// 假设树的结点最大为1005个
const int MAXN = 1005;
vector<int> tree[MAXN]; // 每个tree[i]存的为结点i的孩子
vector<int> path;       // 存储遍历路径
int count = 0;          // 用于顿号末尾不输出
//*************************************************
//		 dfs改编遍历二叉树根到叶子节点路径
//*************************************************
void dfs(int node)
{
    path.push_back(node);   // node入栈
    if (tree[node].empty()) // 即node叶子结点，则要依次输出其路径
    {
        if (count) // 第一组路径不用输出‘、’其余都要输出‘、’
        {
            cout << "、";
        }
        for (size_t i = 1; i < path.size(); i++)
        {
            cout << path[i];
            if (i < path.size() - 1)
            {
                cout << "-";
            }
        }
        count++;
    }
    else // node不为叶子结点
    {
        // for (int child : tree[node])
        for (size_t i = 0; i < tree[node].size(); i++)
        {
            dfs(tree[node][i]); // 只要不是叶子节点，便对其孩子深搜遍历
        }
    }
    path.pop_back(); // 弹栈回溯
}

int main()
{
    int N; // 代表N个结点
    cout << "请输入节点数目：";
    cin >> N;

    cout << "请输入" << N << "个节点对应根节点：";
    for (int i = 1; i <= N; i++)
    {
        int parent;
        cin >> parent;
        tree[parent].push_back(i); // 将parent的孩子全部入栈
    }
    // dfs深搜从根节点开始
    cout << "根节点到叶节点的路径：";
    dfs(0);

    cout << endl;
    system("pause");
    return 0;
}
/*
请输入节点数目：7
请输入7个节点对应根节点：0 5 5 1 4 1 4
根节点到叶节点的路径：1-4-5-2、1-4-5-3、1-4-7、1-6
*/