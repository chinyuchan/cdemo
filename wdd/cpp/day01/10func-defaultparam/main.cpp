#include <iostream>
using namespace std;

void func(int a, int b=1024) {
    cout << a << ", " << b << endl;
}



int main()
{
    func(10);
    func(10, 20);

    return 0;
}
