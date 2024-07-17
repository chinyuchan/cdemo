#include <iostream>
using namespace std;

// extern "C"的主要作用就是为了能够正确实现C++代码调用其他C语言代码。加上extern "C"后，会指示编译器这部分代码按C语言的进行编译，而不是C++的。
// 由于C++支持函数重载，因此编译器编译函数的过程中会将函数的参数类型也加到编译后的代码中，而不仅仅是函数名；
// 而C语言并不支持函数重载，因此编译C语言代码的函数时不会带上函数的参数类型，一般只包括函数名。
extern "C" {
    // C编译后的函数名：hi
    // C++编译后的函数名：Z2hiv
    void hi() {
        cout << "Hi" << endl;
    }

    // C编译后的函数名：hello
    // C++编译后的函数名：Z5helloRKNSt7
    void hello(const string& name) {
        cout << "Hello" << ' ' << name <<endl;
    }
}

int main() {
    hi();
    hello("cdd");

    cout << true << ' ' << false << endl; // 1 0
    cout << boolalpha << true << ' ' << false << endl; // true false

    return 0;
}
