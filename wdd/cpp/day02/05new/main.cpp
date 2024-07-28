#include <iostream>
using namespace std;

int main()
{
    // 会初始化为0
    int* pi = new int;
    cout << *pi << endl;
    delete pi;

    pi = new int(1024);
    cout << *pi << endl;
    delete pi;

    pi = new int{1314}; // C++11
    cout << *pi << endl;
    delete pi;

    return 0;
}
