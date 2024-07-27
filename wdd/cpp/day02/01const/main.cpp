#include <iostream>
using namespace std;

int main()
{
    // 编译期就能确定
    const int a = 1024;
    int* p = (int*)&a;
    *p = 9527;
    cout << "*p=" << *p << endl;
    // 使用a的地方，都用a的值进行了替换
    cout << "a=" << a << endl;
    cout << "p=" << p << endl;
    cout << "&a=" << &a << endl;

    // 证明a是常量
    int arr[a]{};

    int x = 10, y = 20;
    // 运行时才能确定
    const int c = x + y; // 不是常量
    p = (int*)&c;
    *p = 1314;
    cout << c << endl;

    return 0;
}
