#include <iostream>
#include <algorithm>
using namespace std;
typedef struct Msort
{
	int count;
	int value;
}MS;

//*********************************************************************************
//		 sort_rule 函数，对 Array 数组进行排序。排序的依据是首先按照出现次数 count 的降序排列
//       如果次数相同，则按照数值 value 的升序排列
//*********************************************************************************
bool sort_rule(MS A, MS B)
{
	if (A.count == B.count)
		return A.value < B.value;
	return A.count > B.count;
}
int main()
{
	int n;
	MS Array[1005];
	cin >> n;
	for (int i = 0; i <= 1004; i++)
	{
        //数组的索引 i 被用作哈希函数的输入，而 Array[i].count 则用于存储相应索引 i 处数值的出现次数。
        //这里的哈希函数可以说是简单的恒等映射，即将数值直接映射到数组的相应位置
		Array[i].count = 0;
		Array[i].value = i;
	}
	while (n--)
	{
		int value;
		cin >> value;
		Array[value].count++;
	}
	sort(Array, Array + 1005, sort_rule);
	for (int i = 0; i <= 1004; i++)
	{
		if (Array[i].count)
			cout << Array[i].value << " " << Array[i].count << endl;
	}

    cout << endl;
    system("pause");
    return 0;
}
