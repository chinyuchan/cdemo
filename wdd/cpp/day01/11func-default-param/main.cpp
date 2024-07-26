#include <iostream>
using namespace std;

void func(int a, int b = 1024);


int main()
{
    func(10);
    return 0;
}

// 编译错误
// void func(int a, int b = 1024) {
//     cout << a << ", " << b << endl;
// }

void func(int a, int b) {
    cout << a << ", " << b << endl;
}
