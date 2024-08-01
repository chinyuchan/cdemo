#include <iostream>
using namespace std;

template<typename BASE>
class Shape: public BASE {
public:
    void draw() {
        BASE::draw();
    }
};

class Circle {
public:
    void draw() {
        cout << "draw Circle" << endl;
    }
};
class Square {
public:
    void draw() {
        cout << "draw Square" << endl;
    }
};

int main()
{
    Shape<Circle> s;
    s.draw();

    Shape<Square> s1;
    s1.draw();

    return 0;
}
