#include <iostream>
using namespace std;

class A {
public:
    // 没有必要在构造函数进行初始化
    explicit A(int a = 0) : a(a) {}

    //普通函数可以访问静态属性
    void show() const {
        cout << a << ' ' << b << endl;
    }
    static void bar() {
        cout << "static bar" << endl;
    }
    static void func() {
        cout << "static func" << endl;
        // 静态函数不能访问非静态成员
        // cout << a << endl;
        // show();
        cout << b << endl;
        bar();
    }
private:
    int a;
    static int b;
};

// 在定义的时候进行初始化
int A::b = 10;


int main()
{
    A a(1);
    a.show();
    a.func();
    A::func();

    return 0;
}
