#include <iostream>
using namespace std;

void func(int) {
    cout << "func(int)" << endl;
}

void func() {
    cout << "func()" << endl;
}

int main()
{
    func(10);
    func(20);
    func();

    return 0;
}
