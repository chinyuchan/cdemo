#include <iostream>
using namespace std;

struct Father{};
struct Son:Father{};

int main() {
    int a = 10;
    // 任意类型指针都能隐式转换为void*
    void* p = &a;
    // void*不能隐式转换为其他类型指针
    // int* pa = p;
    int* pa = static_cast<int*>(p);
    cout << *pa << endl;

    double d = static_cast<double>(a);

    // 子类指针可以隐式转换为父类指针，反之则不可以
    Son s;
    Father* pf = &s;
    Son *ps = static_cast<Son*>(pf);




    return 0;
}
