#include <iostream>
using namespace std;

void func() {
    cout << "func()" << endl;
}

void func(int a) {
    cout << "func(int)" << endl;
}

extern "C" {
    void bar() {
        cout << "bar()" << endl;
    }

    // 编译错误
    // void bar(int a) {
    //     cout << "bar(int)" << endl;
    // }
}


int main() {
    // call	_Z4funcv
    func();

    // call	_Z4funci
    func(10);

    // call	bar
    bar();

    return 0;
}
