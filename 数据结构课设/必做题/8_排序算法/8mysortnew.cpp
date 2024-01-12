#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
#include <random>
#include <chrono>
#include <windows.h>
using namespace std;
#define RANDOM_SAMPLE 1
#define INCREASE_SAMPLE 2
#define DECRESSE_SAMPLE 3
#define SAMPLE_MAX_NUM 50000
#define int_max 1e9

//********************************************
//			函数声明
//********************************************
void CreateTestSamples(ofstream &fileOut, int mode);
vector<int> LoadSample(ifstream &fileIn);
template <class T>
void Swap(T &numA, T &numB);
void InsertSort(int *list, int n);
void ShellSort(int list[], int n, vector<int> increase);
void ShellSortIner(int list[], int increase, int n);
void BubbleSort(int list[], int n);
int Partation(int list[], int start, int end);
void QuickSortIner(int list[], int start, int end);
void QuickSort(int list[], int n);
void SelectSort(int list[], int n);
void MaxHeapify(int list[], int i, int heapSize);
void HeapSort(int list[], int n);
void MergeSort(int list[], int n);
void MergeSort(int list[], int n, int len);
void Merge(int list[], int start, int mid, int end);
void RedixSort(int list[], int n);

//*************************************************
//		在文件中创建一个测试用例
//*************************************************
void CreateTestSamples(ofstream &fileOut, int mode)
{
    if (mode == RANDOM_SAMPLE)
    {
        // 构造函数接受一个种子值，这里使用 `time(0)` 获取当前时间作为种子。
        //(unsigned int)` 强制类型转换用于将 `time(0)` 的结果转换为无符号整数
        default_random_engine myRandomEngine((unsigned int)time(0)); // default_random_engine` 是C++标准库提供的一个随机数引擎类
        uniform_int_distribution<int> myIntDistribution(0, int_max); // 用于生成均匀分布整数的类,范围为从0到int_max
        for (int i = 1; i <= SAMPLE_MAX_NUM; ++i)
        {
            fileOut << myIntDistribution(myRandomEngine) << " ";
        }
    }
    else if (mode == DECRESSE_SAMPLE)                                // 生成递减序列样本
    {
        for (int i = SAMPLE_MAX_NUM; i >= 1; --i)
        {
            fileOut << i << " ";
        }
    }
    else if (mode == INCREASE_SAMPLE)                                // 生成递增序列样本  
    {
        for (int i = 1; i <= SAMPLE_MAX_NUM; ++i)
        {
            fileOut << i << " ";
        }
    }

    return;
}
//*************************************************
//		 加载一个测试用例，保存于vector中并返回
//*************************************************
vector<int> LoadSample(ifstream &fileIn)
{
    vector<int> sample;
    for (int i = 0; i <= SAMPLE_MAX_NUM; ++i)
    {
        int sampleNum;
        fileIn >> sampleNum;
        sample.emplace_back(sampleNum);
    }

    return sample;
}
//*************************************************
//		 交换两个数的模板函数
//*************************************************
template <class T>
void Swap(T &numA, T &numB)
{
    T temp = numB;
    numB = numA;
    numA = temp;
}
//*************************************************
//		 直接插入排序算法
//*************************************************
void InsertSort(int *list, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int temp = list[i];
        int j = i - 1;
        while (j >= 0 && list[j] > temp)                             // 寻找插入位置
        {
            list[j + 1] = list[j];                                   // 移位
            --j;
        }
        list[j + 1] = temp;
    }

    return;
}
//*************************************************
//		 希尔排序的按每趟增量的函数
//*************************************************
void ShellSortIner(int list[], int increase, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int temp = list[i];
        int j = i - increase;
        while (j >= 0 && list[j] > temp)
        {
            list[j + increase] = list[j];                            // 注意增量不是1了，所以得j -= increase
            j -= increase;
        }
        list[j + increase] = temp;
    }

    return;
}
//*************************************************
//		 希尔排序，vector<int> increase储存着增量
//*************************************************
void ShellSort(int list[], int n, vector<int> increase)
{
    for (size_t i = 0; i < increase.size(); ++i)
    {
        ShellSortIner(list, increase[i], n);
    }
}
//*************************************************
//		 冒泡排序 ，按趟数逐个交换
//*************************************************
void BubbleSort(int list[], int n)
{

    for (int i = 0; i < n; ++i)
    {
        bool has_swap = false;
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (list[j] > list[j + 1])
            {
                Swap(list[j + 1], list[j]);
                has_swap = true;
            }
        }
        if (has_swap == false)                                       // 如果某趟过程中未交换，则证明序列已经有序
        {
            return;
        }
    }
    return;
}
//*************************************************
//		 具体的一趟快速排序过程
//*************************************************
int Partation(int list[], int start, int end)
{
    std::default_random_engine MyrandomEngine((unsigned int)time(0));
    std::uniform_int_distribution<int> myIntDistribution(start, end);// 随机选取中枢值
    int i = start;                                                   // 前指针
    int j = end;                                                     // 后指针
    Swap(list[start], list[myIntDistribution(MyrandomEngine)]);      // 将第一个数随机放回数组中枢中，于是的第一个位置就空了
    int pivotNum = list[start];

    while (j > i)                       
    {
        while (j > i && list[j] >= pivotNum)                         // 小于中枢的就放到前面 
            --j;
        list[i] = list[j];

        while (j > i && list[i] <= pivotNum)                         // 大于中枢的就放在后面
            ++i;
        list[j] = list[i];
    }
    list[i] = pivotNum;
    return i;                                                        // 返回中枢值所在下标
}
//*************************************************
//		 快速排序递归函数
//*************************************************
void QuickSortIner(int list[], int start, int end)
{
    // 序列进行一趟排序以后，分别再对两个子序列进行递归
    if (start < end)
    {
        int pivotLoc = Partation(list, start, end);                  // 一趟快速排序，将中枢传回
        QuickSortIner(list, start, pivotLoc - 1);
        QuickSortIner(list, pivotLoc + 1, end);
    }
    return;
}
//*************************************************
//		 快速排序
//*************************************************
void QuickSort(int list[], int n)
{
    QuickSortIner(list, 0, n - 1);
}
//*************************************************
//		 直接选择排序
//*************************************************
void SelectSort(int list[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minLoc = i + 1;
        for (int j = i + 1; j < n; ++j)
        {
            if (list[minLoc] > list[j])
            {
                minLoc = j;
            }
        }
        Swap(list[i], list[minLoc]);
    }
    return;
}
//*************************************************
//		 堆调整函数
//*************************************************
void MaxHeapify(int list[], int i, int heapSize)
{
    int lchild = 2 * i + 1;
    int rchild = 2 * i + 2;

    while (lchild <= heapSize)
    {
        if (rchild <= heapSize)
        {

            if (list[i] > list[rchild] && list[i] > list[lchild])
                break;
            else if (list[rchild] >= list[lchild])
            { // 左孩子大
                Swap(list[i], list[rchild]);
                i = rchild;
                lchild = 2 * i + 1;
                rchild = 2 * i + 2;
            }
            else if (list[rchild] <= list[lchild])
            { // 右孩子大
                Swap(list[i], list[lchild]);
                i = lchild;
                lchild = 2 * i + 1;
                rchild = 2 * i + 2;
            }
        }
        else
        {
            if (list[i] > list[lchild])
                break;

            else if (list[i] < list[lchild])
            {
                Swap(list[i], list[lchild]);
                i = lchild;
                lchild = 2 * i + 1;
                rchild = 2 * i + 2;
            }
        }
    }

    return;
}
//*************************************************
//		 堆排序
//*************************************************
void HeapSort(int list[], int n)
{
    for (int i = (n - 1) / 2; i >= 0; i--)                           // 建成大顶堆
    {
        MaxHeapify(list, i, n);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        Swap(list[0], list[i]);                                      // 将堆顶记录与最后元素交换
        MaxHeapify(list, 0, i - 1);
    }

    return;
}
//*************************************************
//		 归并排序
//*************************************************
void MergeSort(int list[], int n)
{
    for (int len = 1; len < n; len *= 2)
    {
        MergeSort(list, n - 1, len);
    }
}
//*************************************************
//		 归并排序具体递归
//*************************************************
void MergeSort(int list[], int n, int len)
{
    int i = 0;
    while (i + 2 * len <= n)
    {
        Merge(list, i, i + len - 1, i + 2 * len - 1);
        i = i + 2 * len;
    }

    if (i + len <= n)
    {
        Merge(list, i, i + len - 1, n);
    }
}
//*************************************************
//		 合并两个序列
//*************************************************
void Merge(int list[], int start, int mid, int end)
{
    int *tempList = new int[end - start + 1];
    int i = start;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= end)
    {
        if (list[i] <= list[j])
        {
            tempList[k] = list[i];
            ++k;
            ++i;
        }
        else
        {
            tempList[k] = list[j];
            ++k;
            ++j;
        }
    }

    while (j <= end)
    {
        tempList[k] = list[j];
        ++k;
        ++j;
    }

    while (i <= mid)
    {
        tempList[k] = list[i];
        ++k;
        ++i;
    }

    for (i = start, k = 0; i <= end; ++i, ++k)
    {
        list[i] = tempList[k];
    }

    delete[] tempList;
    return;
}
//*************************************************
//		 基数排序
//*************************************************
void RedixSort(int list[], int n)
{
    queue<int> queue[10];
    long long radix;
    long long maxRadix = int_max * 10;

    for (radix = 10; radix <= maxRadix; radix *= 10)
    {
        // 队列分配
        for (int i = 0; i < n; ++i)
        {
            int digit = (list[i] % radix) / (radix / 10);
            queue[digit].push(list[i]);
        }

        // 队列回收
        int j = 0;
        for (int i = 0; i < 10; ++i)
        {
            while (queue[i].empty() == false)
            {
                list[j] = queue[i].front();
                queue[i].pop();
                ++j;
            }
        }
    }

    return;
}

int main()
{
    //  测试用例生成
    for (int i = 1; i <= 10; ++i)
    {
        string sampleFileNameWrite = "Sample" + to_string(i) + ".txt";
        ofstream Sample(sampleFileNameWrite, ios::out | ios::trunc); // ios::trunc用于清除文件以前内容
        if (Sample.fail())
        {
            cout << sampleFileNameWrite << " file cannot open\n";
            exit(1);
        }
        if (i == 1)
        {
            CreateTestSamples(Sample, INCREASE_SAMPLE); // 生成递增样本
        }
        else if (i == 2)
        {
            CreateTestSamples(Sample, DECRESSE_SAMPLE); // 生成递减样本
        }
        else
        {
            CreateTestSamples(Sample, RANDOM_SAMPLE);
            Sleep(500);
        }
        Sample.close();
    }

    // 测试用例加载
    vector<vector<int>> sampleList(10); // 测试集0-9
    for (int i = 0; i < 10; ++i)
    {
        string sampleFileNameRead = "Sample" + to_string(i + 1) + ".txt";
        ifstream Sample(sampleFileNameRead, ios::in);
        sampleList[i] = LoadSample(Sample);
    }
    cout << "\t\t\t\t排序算法测试\n-------------------------------------------------------------------------------------------------------------\n";
    cout << "排序算法\t升序     倒序    样例3     样例4     样例5     样例6     样例7      样例8     样例9      样例10   \n";
    // clock_t BeginTime;
    // clock_t EndTime;
    int **sample;
    sample = new int *[10];
    for (int i = 0; i < 10; ++i)
    {
        sample[i] = new int[SAMPLE_MAX_NUM];
        memcpy(sample[i], &sampleList[i][0], (sampleList[i].size() - 1) * sizeof(int));
    }

    // 插入排序
    cout << "\nInsert:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        InsertSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms  ";

    }

    // 希尔排序
    const vector<int> shellIncrease = {929, 505, 109, 41, 19, 5, 1};
    cout << "\nShell:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        ShellSort(sample[j], SAMPLE_MAX_NUM, shellIncrease);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms    ";
    }
    // 冒泡排序
    cout << "\nBubble:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        BubbleSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms    ";
    }
    // 快速排序
    cout << "\nQuick:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        QuickSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms    ";
    }
    // 选择排序
    cout << "\nSelect:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        SelectSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms ";
    }
    // 堆排序
    cout << "\nHeap:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        HeapSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms    ";
    }
    // 归并排序
    cout << "\nMerge:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        MergeSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms   ";
    }
    
    // 基数排序
    cout << "\nRedix:\t\t";
    for (int j = 0; j < 10; ++j)
    {
        auto start = chrono::steady_clock::now();
        RedixSort(sample[j], SAMPLE_MAX_NUM);
        auto end = chrono::steady_clock::now();
        chrono::duration<double, milli> processtime = end - start;   // std::milli 表示以微秒为时间单位
        cout << fixed << setprecision(2);                            // 设置输出精度为两位小数
        cout << processtime.count() << "ms   ";
    }
    // 循环每个内层vector,调用clear()清空元素
    // 调用shrink_to_fit()释放未使用的内存
    for (auto &inner : sampleList)
    {
        inner.clear();
        inner.shrink_to_fit();
    }

    for (int i = 0; i < 10; i++)
    {
        delete[] sample[i];
    }
    delete[] sample;

    cout << endl;
    system("pause");
    return 0;
}