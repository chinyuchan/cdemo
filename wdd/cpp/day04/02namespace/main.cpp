#include <iostream>
using namespace std;


class A {
public:
    static void foo() {
        cout << "A::foo()" << endl;
    }
    int x;
    static int a;
};
int A::a = 1024;

int a = 1314;

void foo() {
    cout << "foo()" << endl;
}

namespace mysp {
    void foo() {
        cout << "mysp::foo()" << endl;
    }
}

int s = 1314;

int main()
{
    cout << A::a << endl;
    cout << a << endl;
    A::foo();
    foo();
    mysp::foo();
    int s = 9527;
    cout << s << endl; // 9527 局部优先
    {
        // C语言中访问全局作用域
        extern int s;
        cout << s << endl; // 1314
    }
    cout << ::s << endl; // 指明用全局的

    return 0;
}
