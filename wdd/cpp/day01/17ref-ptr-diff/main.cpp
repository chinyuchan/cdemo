#include <iostream>
using namespace std;


int main()
{
    char a = 'x';
    int b = 1024;
    double d = 3.14;
    char* pa = &a;
    int* pb = &b;
    double* pd = &d;

    cout << sizeof(pa) << endl;
    cout << sizeof(pb) << endl;
    cout << sizeof(pd) << endl;

    char& ra = a;
    int& rb = b;
    double& rd = d;

    cout << sizeof(ra) << endl;
    cout << sizeof(rb) << endl;
    cout << sizeof(rd) << endl;
    return 0;
}
