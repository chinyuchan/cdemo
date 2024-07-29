#include <iostream>
using namespace std;


int main()
{
    const int a = 1024;
    // const_cast<int>(a);
    const int& ra = a;
    int& r = const_cast<int&>(ra);
    cout << r << endl;
    r = 1314;
    cout << r << endl;
    int* p = const_cast<int*>(&a);
    cout << *p << endl;

    return 0;
}
