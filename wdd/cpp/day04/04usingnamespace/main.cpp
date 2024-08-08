#include <iostream>
using namespace std;

namespace n1 {
    int g = 1024;
}

namespace n2 {
    int g = 1314;
}

int main()
{
    cout << n1::g << endl;
    cout << n2::g << endl;

    using namespace n1;
    cout << g << endl; // n1::g

    using namespace n2;
    // cout << g << endl; // ERROR 歧义
    cout << n1::g << endl;
    cout << n2::g << endl;
    // int g = 9527; // ERROR
    using n1::g; // 引入当前作用域
    cout << g << endl; // n1::g
    cout << n1::g << endl;
    cout << n2::g << endl;

    //using n2::g; // ERROR 歧义

    return 0;
}
