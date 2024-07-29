#include <iostream>
using namespace std;

struct Father {
    virtual void func(){}
};

struct Son: Father {

};


struct Animal {
    virtual void eat(){}
};

struct Dog :Animal {

};
struct Cat: Animal {

};

int main()
{
    Son s;
    Father* pf = &s;
    Son* ps = dynamic_cast<Son*>(pf);

    Dog d;
    Animal* pa = &d;
    Cat* pc1 = static_cast<Cat*>(pa);
    cout << pc1 << endl;

    // 会转换失败
    Cat* pc2 = dynamic_cast<Cat*>(pa);
    cout << pc2 << endl;

    Dog* pd = dynamic_cast<Dog*>(pa);
    cout << pd << endl;

    return 0;
}
