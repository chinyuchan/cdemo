#include <iostream>
using namespace std;

struct A {
    int a;
};

struct F {
    int c;
};
struct B:A,F {
    int b;
};

int main()
{
    int num = 0x12345678;
    char* pc = reinterpret_cast<char*>(&num);
    cout << *pc << endl;
    cout << hex << (int)*pc << endl;

    int* pi = reinterpret_cast<int*>(0x123456ff);
    long int address = reinterpret_cast<long int>(&num);


    B b;
    cout << "&b = " << &b << endl;
    F* pf = &b;
    cout << "pf = " << pf << endl;
    B* pb = static_cast<B*>(pf);
    cout << "pb = " << pb << endl;
    // 不能用重解释类型转换
    B* pb1 = reinterpret_cast<B*>(pf);
    cout << "pb1 = " << pb1 << endl;

    return 0;
}
