#include <iostream>
using namespace std;

class X {
public:
    explicit X(int a = 0, int b = 0) : a(a), b(b) {}
    void show() const {
        cout << a << ' ' << b << endl;
    }
    void func() const {
        a = 1;
    }

    mutable int a;
    int b;
};

int main()
{
    X x;
    x.show();
    x.func();
    x.show();

    const X obj;
    obj.a = 1314;
    obj.show();
    return 0;
}
