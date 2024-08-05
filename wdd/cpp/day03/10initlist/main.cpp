#include <iostream>
using namespace std;

class A {
public:
    A() : a(10) {}
private:
    const int a; // 常量必须初始化
};

class B {
public:
    B(int& r) : ref(r) {}
private:
    int& ref; // 引用必须初始化
};


class C {
public:
    C(int x) : x(x){}
private:
    int x;
};

class D {
public:
    D() : c(10){}
private:
    C c; // C没有无参构造
};

int main() {
    A a;
    int x = 10;
    B b(x);
    D d;

    return 0;
}
