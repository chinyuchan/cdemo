#include <iostream>
using namespace std;

class S {
public:
    int a;

    // static改变了变量的存储位置
    static int b;
};

// 静态属性类外定义
int S::b = 10;

int main()
{
    cout << sizeof(S) << endl;

    S s1, s2;
    cout << s1.a << ' ' << s1.b << endl;

    s1.b = 1314;
    cout << s2.a << ' ' << s2.b << endl;

    cout << &s1.b << endl;
    cout << &s2.b << endl;

    cout << S::b << endl;
    S::b = 9527;
    cout << S::b << endl;

    return 0;
}
