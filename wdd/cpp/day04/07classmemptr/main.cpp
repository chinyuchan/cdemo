#include <iostream>
using namespace std;
class A {
public:
    explicit A(int a=0, int b=0) : a(a), b(b) {

    }
    void show() {
        cout << "show: " << a << ' ' << b << endl;
    }
    int a;
    int b;
};

int main()
{
    // 成员变量指针
    int A::* pm = &A::b;
    cout << pm << endl;

    // 成员函数指针
    void (A::*pf)() = &A::show;
    cout << pf << endl;

    // 成员指针不能直接解引用，需要用对象才能解引用
    A obj(123, 456);
    (obj.*pf)();
    cout << obj.*pm << endl; // 456

    obj.*pm = 1024;
    A* pa = &obj;
    cout << pa->*pm << endl; // 1024
    (pa->*pf)();

    pm = &A::a;
    obj.a = 9527;
    cout << obj.*pm << endl; // 9527

    return 0;
}
