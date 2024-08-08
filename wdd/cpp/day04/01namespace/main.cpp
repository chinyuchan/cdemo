#include <iostream>
using namespace std;

void foo() {
    cout << "foo()" << endl;
}

int g = 1024;

namespace mysp {
    int g = 1314;
}

namespace mysp {
    void foo() {
        cout << "mysp::foo()" << endl;
        cout << g << endl;
    }
}


int main()
{
    foo();
    mysp::foo();
    cout << g << endl;
    cout << mysp::g << endl;

    return 0;
}
