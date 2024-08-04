#include <iostream>
using namespace std;

class Emp {
public:
    Emp(const int no, const string& name, const float sal) : _no(no), _name(name), _sal(sal) {}

    void info() const {
        cout << _no << ' ' << _name << ' ' << _sal << endl;
    }

private:
    int _no;
    string _name;
    float _sal;
};

class Circle {
public:
    explicit Circle(const double r) : _r(r) {}
    [[nodiscard]] double perimeter() const { return 2 * 3.14 * _r; }
    [[nodiscard]] double area() const { return 3.14 * _r * _r; }

private:
    double _r;
};


int main() {
    Emp e(1001, "bdd", 10000.0);
    e.info();

    Circle c(1.5);
    cout << c.perimeter() << endl;
    cout << c.area() << endl;

    return 0;
}
