#include <iostream>
using namespace std;

int main()
{
    int a = 1024;
    int b(1314);
    int arr[5] = {0, 1, 2, 3, 4};
    string s("hello");

    // 初始化的方式太多了
    //C++11中提出了统一初始化表
    int c{9527};
    cout << c << endl;
    int brr[5]{0,1,2,3,4};
    for(auto n: brr) {
        cout << n << ' ';
    }
    cout << endl;
    string s1{"world"};
    cout << s1 << endl;

    return 0;
}
