#include <iostream>
using namespace std;

void func() {
    cout << "::func()" << endl;
}

void foo(int x) {
    cout << "::foo(int)" << endl;
}

class X {
public:
    void func() {
        cout << "X::func()" << endl;
    }

    void foo() {
        cout << "X::foo()" << endl;
    }

    void run() {
        func();
        ::func();

        // 引入当前作用域，构成重载
        using ::foo;
        foo(1);
    }
};

int main()
{
    X x;
    x.run();

    return 0;
}
