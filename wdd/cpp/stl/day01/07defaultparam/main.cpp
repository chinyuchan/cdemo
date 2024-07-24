#include <iostream>
using namespace std;

template<typename T = int>
void func() {
    cout << typeid(T).name() << endl;
    T a;
}

template <typename T = int, typename U = double>
void bar() {
    T a;
    U b;
    cout << typeid(T).name() << ' ' << typeid(U).name() << endl;
}

int main() {
    func<>();
    func();
    func<double>();
    func<char>();

    bar();
    bar<char>();
    bar<char,int>();

    return 0;
}
