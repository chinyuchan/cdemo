#include <iostream>
using namespace std;

class Object {
public:
    explicit Object(int x=0, int y=0) : x(x), y(y) {}
    void show() const {
        cout << x << ' ' << y << endl;
    }
private:
    int x;
    int y;
};


int main()
{
    Object obj;
    const Object obj2;
    obj.show();
    obj2.show();

    const Object* p = &obj;
    p->show();

    return 0;
}
