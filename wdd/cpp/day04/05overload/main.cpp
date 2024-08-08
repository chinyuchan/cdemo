#include <iostream>
using namespace std;

namespace n1 {
    void foo(int n) {
        cout << "n1::foo(int)" << endl;
    }
}
namespace n2 {
    void foo(double n) {
        cout << "n2::foo(double)" << endl;
    }
}

int main()
{
    int a = 10;
    double b = 3.14;
    n1::foo(a);
    n1::foo(b);
    n2::foo(a);
    n2::foo(b);
    cout << "--------------------" << endl;
    using namespace n1;
    foo(a);
    foo(b);
    cout << "--------------------" << endl;
    using namespace n2;
    foo(a);
    foo(b);
    cout << "--------------------" << endl;
    using n1::foo;
    foo(a);
    foo(b);
    cout << "--------------------" << endl;
    using n2::foo;
    foo(a);
    foo(b);

    return 0;
}
