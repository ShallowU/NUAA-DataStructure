#include <iostream>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define maxsize 100 // 假设每个栈最大容量为30

typedef struct initstack // 结构化栈
{
    double *top;
    double *base;
    int stacksize;
} SqStack;
//*************************************************
//		 给栈进行初始化
//*************************************************
void InitStack(SqStack &s)
{
    s.base = new double[maxsize];
    if (!s.base)
        cout << "初始化栈,内存分配失败" << endl;
    s.top = s.base;
    s.stacksize = maxsize;
}
//*************************************************
//		  查看栈是否为空
//*************************************************
bool StackEmpoty(SqStack s)
{
    if (s.base == s.top)
        return true;
    else
        return false;
}
//*************************************************
//		 栈的使用长度
//*************************************************
int StackLength(SqStack s)
{
    return s.top - s.base;
}
//*************************************************
//		 栈中添加元素
//*************************************************
void Push(SqStack &s, double e)
{
    if (s.top - s.base == s.stacksize)
        cout << "栈已经满！" << endl;
    *s.top++ = e;
    //*s.top=e;
    // s.top++;
}
//*************************************************
//		 栈中弹出元素
//*************************************************
double Pop(SqStack &s)
{
    if (s.top == s.base)
    {
        cout << "栈为空" << endl;
        return 0;
    }
    --s.top;
    double e = *s.top; // e=*--s.top
    return e;
}
//*************************************************
//		 返回栈中顶元素
//*************************************************
double peek(SqStack s)
{
    s.top--;
    double e = *s.top;
    s.top++;
    return e;
}
//*************************************************
//		 判断运算符号优先级，用数字大小来比较
//*************************************************
int Priority(int oper)
{
    if (oper == '*' || oper == '/' || oper == '%')
    {
        return 1;
    }
    else if (oper == '+' || oper == '-')
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
//*************************************************
//		 判断是否为运算符号
//*************************************************
bool Isoper(char val)
{
    if (val == '*' || val == '/' || val == '+' || val == '-' )//|| val == '%'
        return true;
    else
        return false;
}
//*************************************************
//		 运算一组数，从数字栈取出两个数，符号栈取出一个符号
//*************************************************
double calculate(double num1, double num2, int oper)
{
    double res = 0.0;
    switch (oper)
    {
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num2 - num1; // 注意顺序
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            if(abs(num1)<0.000001) // 判断除数是否为0
            {
                res = num2 / num1;
                break;
                cout << num2 << "/" << num1 << "过程中存在除数为0情况!错误！计算结束！" << endl;
                exit(1);
            }
            else
            {
                res = num2 / num1;
                break;;
            }
        
        /*
        case '%':
            res = num2 % num1;
            break;
        */
        default:
            break;
    }
    return res;
}
//*************************************************
//		 将栈中剩余运算符和运算数进行运算
//*************************************************
void GetLastRes(SqStack &OperStack, SqStack &NumStack)
{
    char inttochar;
    double num1 = 0.0, num2 = 0.0,result = 0.0;
    int oper = 0;
    while (1) // 将栈中剩下的依次取出计算
    {
        if (StackEmpoty(OperStack))
        {
            break;
        }
        num1 = Pop(NumStack);
        cout<<"操作数:"<<num1<<"出NumStack栈---> ";
        num2 = Pop(NumStack);
        cout<<"操作数:"<<num2<<"出NumStack栈---> ";
        oper = Pop(OperStack);
        inttochar=oper;
        cout<<"运算符:"<<inttochar<<"出OperStack栈---> ";
        cout<<"执行运算:"<<num2<<inttochar<<num1<<"---> ";
        result = calculate(num1, num2, oper);
        cout<<"操作数:"<<result<<"入NumStack栈---> ";
        Push(NumStack, result); // 运算的结果再入栈
    }
}

int main()
{   
    // 定义符号栈和运算数栈
    SqStack NumStack, OperStack;
    InitStack(NumStack);
    InitStack(OperStack);

    char expressing[100]; // 输入的表达式
    cout << "**************************************--->求解算数表达式<-************************************" << endl;
    cout<< endl;
    cout << "请输入算数表达式(以#开始也以#结尾):";
    cin.getline(expressing, 100);
    int i = 0;
    for (i = 0; expressing[i] != '\0';i++);

    int index = 0; // string中索引
    double num1 = 0.0;
    double num2 = 0.0;
    int oper = 0; // oper是int类型而不是char，因为我们只需要oper是代表的什么，比如*是42，char会自动转化为埃斯托玛数字代表的int类型
    double result = 0.0;
    bool FlagDelimiter = false; //判断是第几个界限符
    char ch = ' ',inttochar;
    int intch, intchnext;
    string ConnctNum = ""; // 如果为多位数
    cout<<"输入序列和栈的变化过程:"<<endl;
    while (1)
    {
        ch = expressing[index];
        intch = ch;
        intchnext = expressing[index + 1];
        if (!FlagDelimiter && ch == '#') // 第一个界限符
        {
            FlagDelimiter =true;
            index++;
            cout<<"开始"<<ch<<"界限符---> ";
            continue;
        }
        else if (ch == '#' && FlagDelimiter) // 第二个界限符
        {
            cout<<"结尾"<<ch<<"界限符---> ";
            break;
        }
        else if (intch >= 48 && intch <= 57) // 当前这位为数字
        {
            ConnctNum += ch;
            // intchnext==46表示为小数点'.'
            while ((intchnext >= 48 && intchnext <= 57)||intchnext==46) // 如果下一位仍为数字，即为多位数
            {
                if (index + 1 < i)
                {
                    ConnctNum += expressing[index + 1];
                    index++;
                    intchnext = expressing[index + 1];
                }
                else
                {
                    break;
                }
            }
            cout<<"操作数:"<<stod(ConnctNum)<<"入NumStack栈---> ";
            Push(NumStack, stod(ConnctNum)); // 数字入栈
            ConnctNum = "";                  // 再初始化
        }
        else if(ch==' ')
        {
            cout<<"空格跳过---> ";
            index++;
            continue;
        }
        else if (ch == '(') // 左括号直接入栈
        {
            cout<<"界限符:(入OperStack栈---> ";
            // int a='(';
            Push(OperStack, ch);
        }
        else if (ch == ')') // 右括号则要把两个括号之间的算完
        {
            cout<<"界限符:)入OperStack栈后立马出栈---> ";
            while (!StackEmpoty(OperStack) && peek(OperStack) != '(') // 括号之间的运算符要算完
            {
                num1 = Pop(NumStack);
                cout<<"操作数:"<<num1<<"出NumStack栈---> ";
                num2 = Pop(NumStack);
                cout<<"操作数:"<<num2<<"出NumStack栈---> ";
                oper = Pop(OperStack);
                inttochar=oper;
                cout<<"运算符:"<<inttochar<<"出OperStack栈---> ";
                cout<<"执行运算:"<<num2<<inttochar<<num1<<"---> ";
                result = calculate(num1, num2, oper);
                cout<<"操作数:"<<result<<"入NumStack栈---> ";
                Push(NumStack, result); // 运算的结果再入栈
            }
            cout<<"界限符:(出OperStack栈---> ";
            Pop(OperStack); // pop the '('
            // cout<<tmp<<endl;tmp=40
        }
        else if (Isoper(ch)) // 为运算符
        {
            if (StackEmpoty(OperStack)) // 运算符号栈为空栈
            {
                cout<<"运算符:"<<ch<<"入OperStack栈---> ";
                Push(OperStack, ch);
            }
            else
            {
                if (Priority(ch) <= Priority(peek(OperStack))) // 判断运算优先顺序，如果后面的相比栈顶为低级运算符号
                {
                    num1 = Pop(NumStack);
                    cout<<"操作数:"<<num1<<"出NumStack栈---> ";
                    num2 = Pop(NumStack);
                    cout<<"操作数:"<<num2<<"出NumStack栈---> ";
                    oper = Pop(OperStack);
                    inttochar=oper;
                    cout<<"运算符:"<<inttochar<<"出OperStack栈---> ";
                    cout<<"执行运算:"<<num2<<inttochar<<num1<<"---> ";
                    result = calculate(num1, num2, oper);
                    cout<<"操作数:"<<result<<"入NumStack栈---> ";
                    Push(NumStack, result); // 运算的结果再入栈
                    cout<<"运算符:"<<ch<<"入OperStack栈---> ";
                    Push(OperStack, ch);    // 符号进行入栈
                }
                else
                {
                    cout<<"运算符:"<<ch<<"入OperStack栈---> ";
                    Push(OperStack, ch); // 运算符优先
                }
            }
        }
        else
        {
            if (ch != '\n')
            {
                cout<<endl;
                cout << ch << "不是算数表达式所需要的符号或者数字，故该表达式错误!无法执行！" << endl;
                return 0;
            }
        }
        index++;
    }

    // 计算栈中剩余运算数
    GetLastRes(OperStack, NumStack);
    double res = Pop(NumStack); // 最后一个栈中元素即为运算结果
    cout<<"最终结果:"<<res<<"出NumStack栈"<<endl;
    cout<<endl;
    cout << "该表达式计算结果为:";
    cout << expressing << " = " << res << endl;

    system("pause");
    return 0;
}
// #6+15*(21-8/4)#