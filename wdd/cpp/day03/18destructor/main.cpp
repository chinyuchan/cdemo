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

A obj;

int main()
{
    cout << "main begin" << endl;
    A a;
    cout << "main end" << endl;

    return 0;
}
