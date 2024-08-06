#include <iostream>
using namespace std;

class Circle {
public:
    explicit Circle(double r = 0) : r(r) {}

    // 常方法
    double primeter() const {
        cout << "primeter() const" << endl;
        return 2 * 3.14 * r;
    }

    double primeter() {
        cout << "primeter()" << endl;
        return 2 * 3.14 * r;
    }

    double area() const {
        return 3.14 * r * r;
    }
private:
    double r;
};


int main() {
    Circle c1(10);
    cout << c1.primeter() << endl;
    cout << c1.area() << endl;

    const Circle c2(10);
    // 常对象只能调用常方法
    cout << c2.primeter() << endl;
    cout << c2.area() << endl;

    return 0;
}
