#include <iostream>
using namespace std;

class A {
public:
    A() {
        cout << "A()" << endl;
    }
    ~A() {
        cout << "~A()" << endl;
    }
};

class B : public A {
public:
    B() {
        cout << "B()" << endl;
    }
    ~B() {
        cout << "~B()" << endl;
    }
};

class C : public B {
public:
    C() {
        cout << "C()" << endl;
    }
    ~C() {
        cout << "~C()" << endl;
    }
};

class D {
public:
    D() {
        cout << "D()" << endl;
    }
    ~D() {
        cout << "~D()" << endl;
    }
};

class E {
public:
    E() {
        cout << "E()" << endl;
    }
    ~E() {
        cout << "~E()" << endl;
    }
};

class F {
public:
    F() {
        cout << "F()" << endl;
    }
    ~F() {
        cout << "~F()" << endl;
    }
};

class G : public C {
public:
    G() {
        cout << "G()" << endl;
    }
    ~G() {
        cout << "~G()" << endl;
    }
private:
    D d;
    F f;
    E e;
};

int main()
{
    G g;
    return 0;
}
