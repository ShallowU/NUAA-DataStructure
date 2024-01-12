#include <iostream>
#include <windows.h>
// #include <time.h>
#include <iomanip>
#include <cstdio>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;

struct CurrentProcess
{                         // 当前进程节点
    string name;          // 进程名
    string pid;
    string duration;      // 持续时间
    long compareduration; // long型的持续世界
    long memory;          // 使用内存
    CurrentProcess *next = nullptr;

    CurrentProcess(string name, string duration, long compareduration, long memory)
    {
        this->name = name;
        this->duration = duration;
        this->compareduration = compareduration;
        this->memory = memory;
    }
};
class OneLinkList
{ // 当前进程单向链表类
public:
    CurrentProcess *head; // 头指针
    int length;           // 链表长度

    OneLinkList();                                                                 // 构造函数
    ~OneLinkList();                                                                // 析构函数
    void clone(const OneLinkList &l);                                              // 拷贝函数
    void downSort();                                                               // 降序排列
    void addNode(string name, string duration, long compareduration, long memory); // 向尾部添加节点
    bool findNode(string name);                                                    // 查找结点
    void deleteNode();                                                             // 删除节点
    void showNode();                                                               // 输出节点
};

struct FinishedProcess
{                         // 已结束进程节点
    string name;          // 进程名
    string duration;      // 持续时间
    long compareduration; // long型持续时间
    string endTime;       // 结束时间
    FinishedProcess *pre = nullptr;
    FinishedProcess *next = nullptr;

    FinishedProcess(string name, string duration, string endTime, long compareduration)
    {
        this->name = name;
        this->duration = duration;
        this->endTime = endTime;
        this->compareduration = compareduration;
    }
};
class TwoLinkList
{ // 结束双向链表类
public:
    FinishedProcess *head; // 头指针
    FinishedProcess *tail;
    int length; // 链表长度

    TwoLinkList();                                                                    // 构造函数
    ~TwoLinkList();                                                                   // 析构函数
    void addNode(string name, string duration, string endTime, long compareduration); // 向头部添加节点
    void UpSortByTime();
    void deleteNote();
    void showNode(); // 输出节点
};

OneLinkList::OneLinkList()
{
    head = nullptr;
    ;
    length = 0;
}

OneLinkList::~OneLinkList()
{
    CurrentProcess *temp = head;
    while (head != nullptr)
    {
        head = head->next;
        delete temp; // 释放内存
        temp = head;
    }
    length = 0;
    head = nullptr;
}
//*************************************************
//		 拷贝构造
//*************************************************
void OneLinkList::clone(const OneLinkList &backup)
{
    head = nullptr;
    length = 0;
    if (backup.head != nullptr)
    {
        CurrentProcess *p = backup.head;
        head = new CurrentProcess(p->name, p->duration, p->compareduration, p->memory);
        length++;
        p = p->next;
        CurrentProcess *q = head;
        while (p != nullptr)
        {
            q->next = new CurrentProcess(p->name, p->duration, p->compareduration, p->memory);
            q = q->next;
            length++;
            p = p->next;
        }
    }
}
//*************************************************
//		 按内存大小从大到小冒泡排序
//*************************************************
void OneLinkList::downSort()
{
    CurrentProcess *p, *q;
    CurrentProcess temp("", "", 0, 0);
    for (p = head; p->next != nullptr; p = p->next)
    {
        for (q = p->next; q != nullptr; q = q->next)
        {
            if (p->memory < q->memory)
            {
                temp.memory = p->memory;
                temp.duration = p->duration;
                temp.name = p->name;
                p->memory = q->memory;
                p->duration = q->duration;
                p->name = q->name;
                q->memory = temp.memory;
                q->duration = temp.duration;
                q->name = temp.name;
            }
        }
    }
}
//*************************************************
//		 新添节点
//*************************************************
void OneLinkList::addNode(string name, string duration, long compareduration, long memory)
{
    if (head == nullptr)
    {
        head = new CurrentProcess(name, duration, compareduration, memory);
        length++;
    }
    else
    {
        CurrentProcess *p;
        p = head;
        head = new CurrentProcess(name, duration, compareduration, memory);
        length++;
        head->next = p;
    }
}
//*************************************************
//		 查找某个节点是否存在用于判断已经结束的节点
//*************************************************
bool OneLinkList::findNode(string name)
{
    CurrentProcess *p;
    p = head;
    for (int i = 0; i < length; i++)
    {
        if (p->name != name)
        {
            p = p->next;
        }
        else
        {
            return true;
        }
    }
    return false;
}

void OneLinkList::deleteNode()
{
    CurrentProcess *p = head;
    CurrentProcess *q;
    while (p != nullptr)
    {
        q = p;
        p = p->next;
        delete q; // 释放内存
    }
    length = 0;
    head = nullptr;
    p = nullptr;
    q = nullptr;
}

void OneLinkList::showNode()
{
    CurrentProcess *p;
    p = head;
    if (p == nullptr)
    {
        cout << endl
             << "****当前无活动进程！****" << endl
             << endl;
    }
    else
    {
        cout << endl
             << "--------------------------活动进程-------------------------------------------------------------" << endl
             << endl;
        cout << setw(45) << left << "进程名 和 PID" << setw(35) << left << "   持续时间" << setw(30) << left << "内存使用情况(KB)" << endl;
        while (p)
        {
            cout << setw(40) << left << p->name << setw(40) << left << p->duration << setw(30) << left << p->memory << endl;
            p = p->next;
        }
        cout << endl
             << "--------------------------活动进程-------------------------------------------------------------" << endl
             << endl;
    }
}

TwoLinkList::TwoLinkList()
{
    head = nullptr;
    tail = nullptr;
    length = 0;
}

TwoLinkList::~TwoLinkList()
{
    FinishedProcess *temp = head;
    if (head != nullptr)
    {
        head = head->next;
        delete temp; // 释放内存
        temp = head;
    }
    length = 0;
    head = tail = nullptr;
}

void TwoLinkList::addNode(string name, string duration, string endTime, long compareduration)
{
    if (head == nullptr)
    {
        head = new FinishedProcess(name, duration, endTime, compareduration);
        length++;
        tail = head;
    }
    else
    {
        tail->next = new FinishedProcess(name, duration, endTime, compareduration);
        length++;
        tail->next->next=nullptr;
        tail->next->pre = tail;
        tail = tail->next;
    }
}

void TwoLinkList::deleteNote()
{
    FinishedProcess *p = head;
    FinishedProcess *q;
    while (p != nullptr)
    {
        q = p;
        p = p->next;
        delete q; // 释放内存
    }
    length = 0;
    head = nullptr;
    p = nullptr;
    q = nullptr;
}

void TwoLinkList::UpSortByTime()
{
    FinishedProcess *p, *q;
    FinishedProcess temp("", "", "", 0);

    for (p = head; p != nullptr && p->next != tail->next; p = p->next)
    {
        for (q = p->next; q != tail->next; q = q->next)
        {
            // 从持续时间字符串中提取数字值
            int pDays, pHours, pMinutes, pSeconds;
            int qDays, qHours, qMinutes, qSeconds;

            int result1=sscanf_s(p->duration.c_str(), "%d天%d小时%d分钟%d秒", &pDays, &pHours, &pMinutes, &pSeconds);
            int result2=sscanf_s(q->duration.c_str(), "%d天%d小时%d分钟%d秒", &qDays, &qHours, &qMinutes, &qSeconds);
            if(result1!=4||result2!=4)
            {
                cout << "duration中提取出错" << endl;
                return;
            }
            // 计算总秒数进行比较
            int pTotalSeconds = pDays * 24 * 60 * 60 + pHours * 60 * 60 + pMinutes * 60 + pSeconds;
            int qTotalSeconds = qDays * 24 * 60 * 60 + qHours * 60 * 60 + qMinutes * 60 + qSeconds;

            // 比较并交换数据（如果需要）
            if (pTotalSeconds > qTotalSeconds)
            {
                // 交换p和q之间的数据
                temp.duration = p->duration;
                temp.name = p->name;
                temp.compareduration = p->compareduration;
                temp.endTime = p->endTime;

                p->duration = q->duration;
                p->name = q->name;
                p->compareduration = q->compareduration;
                p->endTime = q->endTime;

                q->duration = temp.duration;
                q->name = temp.name;
                q->compareduration = temp.compareduration;
                q->endTime = temp.endTime;
            }
        }
    }
}


void TwoLinkList::showNode()
{
    FinishedProcess *p;
    p = head;
    if (p == nullptr)
    {
        cout << "****当前无已结束进程！****" << endl;
    }
    else
    {
        cout << endl
             << "--------------------------结束进程--------------------------" << endl
             << endl;
        cout << setw(75) << left << "进程名 和 PID" << setw(20) << left << "持续时间"
             << "结束时间" << endl;
        while (p != tail->next)
        {
            cout << setw(75) << left << p->name << setw(20) << left << p->duration << p->endTime;
            p = p->next;
        }
        cout << endl
             << "--------------------------结束进程--------------------------" << endl
             << endl;
    }
}

time_t SwitchTime(string time)
{ // 将yyyymmddhhmmss转为s
    struct tm toSecond;

    toSecond.tm_year = stoi(time.substr(0, 4)) - 1900;
    toSecond.tm_mon = stoi(time.substr(4, 2)) - 1;
    toSecond.tm_mday = stoi(time.substr(6, 2));
    toSecond.tm_hour = stoi(time.substr(8, 2));
    toSecond.tm_min = stoi(time.substr(10, 2));
    toSecond.tm_sec = stoi(time.substr(12, 2));
    return mktime(&toSecond);
}

string SwitchTime(time_t currentTime)
{ // 将s转为结束时间
    /*second = time(nullptr);
    struct tm todate;
    char timestring[32] ;

    localtime_s(&todate, &second);
    asctime_s(timestring, sizeof(timestring),&todate);
    return timestring;*/
    currentTime = time(nullptr);
    struct tm localTime;

    
    localtime_s(&localTime, &currentTime);

    
    char timeString[26]; // 26 characters are required for the standard format
    asctime_s(timeString, sizeof(timeString), &localTime);
    return timeString;
}

string FormatTime(long time)
{ // 将s转为持续时间
    int days = 0, hours = 0, minutes = 0, seconds = 0;

    days = time / (24 * 60 * 60);
    hours = (time - days * 24 * 60 * 60) / (60 * 60);
    minutes = (time - days * 24 * 60 * 60 - hours * 60 * 60) / 60;
    seconds = time - days * 24 * 60 * 60 - hours * 60 * 60 - minutes * 60;
    return to_string(days) + "天" + to_string(hours) + "小时" + to_string(minutes) + "分钟" + to_string(seconds) + "秒";
}

int main()
{
    FILE *file;                                                                           // 文件流
    char *cmd = (char *)"wmic process get caption,processid,creationdate,workingsetsize"; // 命令行语句
    char result[128] = {0};                                                               // 读取结果数组
    OneLinkList oldCurrentProcess;                                                        // 旧活动进程
    OneLinkList newCurrentProcess;                                                        // 新活动进程
    TwoLinkList finishedProcess;                                                          // 死亡进程

    while (true)
    {
        time_t begin = time(NULL), end; // 程序开始时间和结束时间，用于每秒间隔输出

        newCurrentProcess.deleteNode(); // 清空新活动进程链表
        if ((file = _popen(cmd, "r")) == NULL)
        {
            cout << "Popen Error!" << endl;
            return -1;
        }
        else
        {
            vector<char *> content;
            string name;
            string pid;
            string beginTime;
            string duration;
            long compareduration;
            long memory;
            time_t nowTime;
            char *temp; // 临时变量

            memset(result, 0, 128);   // 初始化置0
            fgets(result, 128, file); // 读取第一行caption、processid、creationdate、workingsetsize不存储
            while (fgets(result, 128, file) != NULL)
            { // 读取每行数据
                if (result[0] == '\r')
                { // 跳过最后回车符
                    continue;
                }
                content.clear(); // 清空vector
                temp = strtok(result, " ");//分解字符串以空格分隔
                do
                {
                    content.push_back(temp);
                    temp = strtok(NULL, " ");
                } while (temp != NULL);
                memory = stol(content.at(content.size() - 2)); // 读取内存大小
                beginTime = content.at(content.size() - 4);    // 读取开始时间
                beginTime = beginTime.substr(0, 14);
                beginTime = to_string(SwitchTime(beginTime));
                nowTime = time(NULL); // 获取当前时间
                compareduration = (long)nowTime - stol(beginTime);
                duration = FormatTime((long)nowTime - stol(beginTime)); // 计算持续时间
                name = "";
                for (size_t i = 0; i < content.size() - 4; i++)
                {
                    name = name + content.at(i) + " ";
                }                                                                         // 拼接进程名（有带空格的进程名）
                pid = content.at(content.size() - 3);                                     // 获取PID
                newCurrentProcess.addNode(name + pid, duration, compareduration, memory); // 读取一行添加一次节点
            }
            newCurrentProcess.downSort();
            newCurrentProcess.showNode(); // 输出活动进程
            if (oldCurrentProcess.length == 0)
            { // 第一次直接覆盖旧活动进程
                oldCurrentProcess.clone(newCurrentProcess);
            }
            else
            { // 之后先对比并添加结束进程再覆盖旧活动进程
                CurrentProcess *p = oldCurrentProcess.head;

                while (p != nullptr)
                {
                    if (!newCurrentProcess.findNode(p->name))
                    {                         // 如果旧进程不存在新进程链表钟，则死亡
                        nowTime = time(NULL); // 获取当前时间
                        string endTime = SwitchTime(nowTime);
                        finishedProcess.addNode(p->name, p->duration, endTime, compareduration);
                    }
                    p = p->next;
                }
                oldCurrentProcess.deleteNode(); // 清空旧活动进程
                oldCurrentProcess.clone(newCurrentProcess);
            }
            finishedProcess.UpSortByTime(); // 按持续时间从小到大排序
            finishedProcess.showNode();     // 输出死亡进程
            //finishedProcess.deleteNote();   // 每打印一遍就清空一次
            if ((_pclose(file)) == -1)
            {
                cout << "Pclose Error!" << endl;
                return -2;
            }
            end = time(NULL);
            while (end - begin < 1)
            { // 如果运行时间不足1秒，则不结束本次循环
                end = time(NULL);
            }
            system("pause");
        }
    }
    return 0;
}