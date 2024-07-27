#include <iostream>
using namespace std;


int main()
{
    // 右值引用引用右值，可以修改（为右值分配内存空间了）
    int&& r = 1024;
    cout << r << endl;
    r = 1314;
    cout << r << endl;


    int a = 1024;
    const int b = 1024;
    // 1024
    int& r1 = a;
    //int& r2 = b; // ERROR
    //int& r3 = 1024; // ERROR

    const int& r4 = a;
    const int& r5 = b;
    const int& r6 = 1024;

    // int&& r7 = a; // ERROR
    // int&& r8 = b; // ERROR
    int&& r9 = 1024;
    r9 = 1314;

    // const int&& r10 =a; // ERROR
    // const int&& r11 = b; // ERROR
    const int&& r12 = 1024;
    //  r12 = 9527; // ERROR

    constexpr int ci = 100;
    // int&& r13 = ci; // ERROR
    // const int&& r13 = ci; // ERROR

    return 0;
}
