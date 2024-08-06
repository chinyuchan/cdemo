#include <iostream>
using namespace std;

class X {
public:
    X(int num) : b(num), a(b) {}
    void show() {
        cout << a << ' ' << b << endl;
    }
private:
    int a;
    int b;
};

int main() {
    X x(1024);
    x.show();
    return 0;
}
