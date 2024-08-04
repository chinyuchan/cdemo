#include <iostream>
using namespace std;

class Cube {
public:
    Cube() : _l(0) { cout << "Cube()" << endl; }
    Cube(int l) : _l(l) { cout << "Cube(int)" << endl; }
private:
    int _l;
};
int main() {
    Cube c1;
    Cube c2(10);

    // 这不是构造一个对象，这是函数声明
    // Cube c3();

    Cube* pc = new Cube();
    delete pc;

    pc = new Cube(10);
    delete pc;

    // 使用同一初始化表
    Cube c4{};
    Cube c5{20};

    pc = new Cube{};
    delete pc;

    pc = new Cube{30};
    delete pc;

    return 0;
}
