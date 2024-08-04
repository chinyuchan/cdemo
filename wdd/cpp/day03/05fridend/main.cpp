#include <iostream>
using namespace std;

class A {
public:
    int _z;
protected:
    int _y;
private:
    int _x;

    // 友元函数
    friend void func();

    // 友元类
    friend class B;
};

void func() {
    A a;
    // 访问了私有和受保护的属性
    a._x =1;
    a._y = 2;
    a._z = 3;
}


class B {
public:
    void show() {
        A a;
        a._x = 10;
        a._y = 20;
        a._z = 30;
    }
};


int main() {
    func();
    B b;
    b.show();


    return 0;
}
