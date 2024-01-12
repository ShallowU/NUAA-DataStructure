#include <iostream>
#include <cstring>//调用strcpy()
#include <cctype>
#include <string>
#include <stdlib.h>
#include <climits>
using namespace std;

typedef struct  //顺序表用于哈夫曼编码的结构体
{
    char val;   //代表的字母
    int weight; //权值，即字母出现频率
    int parent,lch,rch;
    char code[30]; // 存该字母的编码
}HTNode,*HuffmanTree;
typedef char** HuffmanCode;
//*************************************************
//		 用于建立哈夫曼树时寻找parent==0的两个最小值
//*************************************************
void SelectMinTwo(HuffmanTree &HT,int k,int &minIndex1,int &minIndex2)
{
    minIndex1 = minIndex2 = -1;
    // 初始化最小值和次小值
    int minValue = INT_MAX;
    int secondMinValue = INT_MAX;

    // 遍历数组
    for (int i = 1; i <=k; ++i) {
        if(HT[i].parent==0)
        {
            if (HT[i].weight < minValue) {
                // 当前元素小于最小值，更新最小值和次小值的索引
                secondMinValue = minValue;
                minValue = HT[i].weight;
                minIndex2 = minIndex1;
                minIndex1 = i;
            } else if (HT[i].weight< secondMinValue) {
                // 当前元素介于最小值和次小值之间，更新次小值的索引
                secondMinValue = HT[i].weight;
                minIndex2 = i;
            }
        }
    }
}
//*************************************************
//		 用于构建哈夫曼树
//*************************************************
void CreateHuffmanTree(HuffmanTree &HT,int n,int *letterweight,char *letter) // n是文本内容一共出现多少中字母
{
    if(n<=1)
        return;
    int m=2*n-1;
    int i=0,j=0;
    HT=new HTNode[m+1]; // 第一个位置不用
    for(i=1;i<=m;i++)   // 初始化
    {
        HT[i].parent=0;
        HT[i].lch=0;
        HT[i].rch=0;
    }
    for(j=1;j<=n;j++)   // 将要建立的节点放在前面赋值
    {
        HT[j].weight=letterweight[j-1];
        HT[j].val=letter[j-1];
    }
    int s1=0,s2=0;
    for(i=n+1;i<=m;i++) // 开始选择两小建新树
    {
        SelectMinTwo(HT,i-1,s1,s2); // 寻找parent==0的两个最小值下标
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lch=s1;
        HT[i].rch=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;

    }
}
//*************************************************
//		 用于哈夫曼树的编码
//*************************************************
void CreateHuffmanCode(HuffmanTree &HT,HuffmanCode &HC,int n)
{
    HC=new char *[n+1];  // 先对每一个行指针分配空间
    char *cd;
    cd=new char[n];
    cd[n-1]='\0';        // 不要忘记最后一个给‘\0’
    for(int i=1;i<=n;i++)
    {
        int start=n-1;   // 从后往前写入，这样拷贝时候不用reverse
        int c=i;
        int f=HT[i].parent;
        while (f!=0)     // 到达根节点
        {
            --start;
            if(HT[f].lch==c)
                cd[start]='0';
            else
                cd[start]='1';
            c=f;
            f=HT[c].parent;
        }
        HC[i]=new char[n-start]; //根据n-start给 HC[i]分配空间
        strcpy(HC[i],&cd[start]);
        strcpy(HT[i].code,HC[i]);
    } 
    delete cd;
}
//*************************************************
//		 用于文本打印译码
//*************************************************
void PrintCode(HuffmanTree HT,string expressing,int count,string &connectcode)
{
    size_t i = 0;
    int j = 1;
    for(i=0;i<expressing.length();i++)
    {
        for(j=1;j<=count;j++)
        {
            if(expressing[i]==HT[j].val)
            {
                cout<<HT[j].code;  //打印出每个字母代表的译码
                connectcode+=HT[j].code;
            }
        }
    }
}
//*************************************************
//		 用于哈夫曼树解码
//*************************************************
void DeCode(HuffmanTree HT,string connectcode,int count)
{
    string tmp="";
    size_t i = 0;
    int j=1;
    for(i=0;i<connectcode.length();i++)
    {
        // 每次加一位就遍历是否有出现对应的编码
        tmp+=connectcode[i];
        for(j=1;j<=count;j++)
        {
            if(tmp==HT[j].code)
            {
                cout<<HT[j].val;
                tmp=""; // 打印后再次清零
            }
        }
    }
}

int main()
{
    string expressing;
    HuffmanTree HT;
    HuffmanCode HC;
    cout<<"***************************************->哈夫曼树编码<-*******************************************"<<endl;
    cout<<"请输入由只英文字母构成的文本内容：";
    cin>>expressing;

    size_t i=0;
    for(i=0;i<expressing.length();i++)
    {
        if(expressing[i]>='a'&&expressing[i]<='z')
        {
            expressing[i]=toupper(expressing[i]); // 由于不区分大小写，全转为大写字母统一处理
        }
        else if(expressing[i]>='A'&&expressing[i]<='Z')
        {
            continue;
        }
        else if(expressing[i]==' ')
        {
            continue;
        }
        else
        {
            cout<<expressing[i]<<"不是英文字母，文本内容有问题！编码终止！"<<endl;
            exit(1);
        }
    }
    // 用于统计字母出现频率
    char letter[27] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
                        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','\0'};
    int letterweight[26]={0}; // 用于统计各个字母出现的频率，即分配权重
    string connectcode="";
    int count=0; // 统计一共出现了多少种字母
    size_t j = 0;
    for(i=0;i<expressing.length();i++)
    {
        for(j=0;j<26;j++)
        {
            if(expressing[i]==letter[j])
            {
                letterweight[j]++;
            }
        }
    }
    for(j=0;j<26;j++)
    {
        if(letterweight[j]!=0)
            count++;
    }

    int letterweightnot0[count];        // 将出现过的字母种类放在一个数组中
    char *letternot0=new char[count+1]; // letterweightnot0[count]对应的字母
    letternot0[count]='\0';
    //cout<<"count="<<count<<endl;
    int k = 0;
    for(j=0;j<26;j++)
    {
        if(letterweight[j]!=0)          // 将出现过的字母封装，一个存出现次数，一个存代表字母
        {
            letterweightnot0[k]=letterweight[j];
            letternot0[k]=letter[j];
            k++;
        }
    }
    //cout<<"k="<<k<<endl;
    CreateHuffmanTree(HT,count,letterweightnot0,letternot0);
    CreateHuffmanCode(HT,HC,count);
    //cout<<expressing<<endl;
    cout<<"该文本由哈夫曼树编码为：";
    PrintCode(HT,expressing,count,connectcode);
    cout<<endl;
    cout<<"该解码为(全部转换为大写字母):";
    DeCode(HT,connectcode,count);
    
    cout<<endl; 
    system("pause");    
    return 0;
}
