#include <iostream>
using namespace std;

class A {
public:
    A(int a, int b) : _a(a), _b(b) {}

    int a() const { return _a; }

    int b() const { return _b; }

    template<typename T>
    T combine() {
        return T(_a+_b);
    }

    template<typename T, typename U>
    void show(T x, U y)const {
        cout << x << ", " << y << endl;
    }
private:
    int _a;
    int _b;
};

int main() {
    A a(10, 20);
    cout << a.a() << endl;
    cout << a.combine<int>() << endl;
    a.show(10, "hello");

    return 0;
}
