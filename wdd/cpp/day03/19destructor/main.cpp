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


int main()
{
    //malloc不会调用构造函数
    A* pa = static_cast<A*>(malloc(sizeof(A)));
    // free不会调用析构函数
    free(pa);

    cout << "--------------------" << endl;
    pa = new A;
    delete pa;

    return 0;
}
