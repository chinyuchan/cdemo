#include <iostream>
using namespace std;

template<typename T>
class B {
public:
    explicit B(T data) : _data(data) {}
private:
    T _data;
};

// 模板类参数
template<typename T, template<typename L>class C>
class A {
public:
    explicit A(T a): _a(a) {}

    // 模板类成员
    template<typename N> class X {
    public:
        X(N n) : _n(n) {}
        T n() { return _n; }
        void show() { cout << _n << endl; }
    private:
        N _n;
    };

    void foo() {
        X<int> x(10);
        cout << "X::_n = " << x.n() << endl;
    }

    template<typename M> class Y;

private:
    C<T> _a;
};

// 类外实现
template<typename T, template<typename L>class C>
template<typename M>
class A<T, C>::Y {
public:
    Y(M y) : _y(y) {}
    void show() {
        cout << "Y::_y = " << _y << endl;
    }
private:
    M _y;
};

int main()
{
    A<int, B> a(0);
    a.foo();

    A<int, B>::X<int> x(1024);
    x.show();

    A<int, B>::Y<char> y('a');
    y.show();

    return 0;
}
