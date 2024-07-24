#include <iostream>
using namespace std;

template<typename T>
void func(T a) {
    cout << typeid(T).name() << endl;
    cout << "func(T)" << endl;
}

template<typename T>
void func(T* a) {
    cout << typeid(T).name() << endl;
    cout << "func(T*)" << endl;
}


int main() {
    int a = 123;
    func(&a);

    return 0;
}
