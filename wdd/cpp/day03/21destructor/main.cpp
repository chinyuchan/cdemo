#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A()" << endl;
    }
    ~A() {
        cout << "~A()" << endl;
    }
};


A* pa = new A;

int main()
{
    // 堆对象析构取决于什么时候delete
    delete pa;

    // 栈对象析构取决于其生命周期
    {
        A a;
    }

    return 0;
}
