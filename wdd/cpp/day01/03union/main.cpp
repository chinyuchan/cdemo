#include <iostream>

int main() {
    // 相当于定义了三个变量，它们以联合的方式进行内存布局
    union {
        int a;
        int b;
        char c;
    };

    std::cout << &a << std::endl;
    std::cout << &b << std::endl;
    std::cout << (void*)&c << std::endl; // cout对于char*是直接输出字符串
    a = 97;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;

    return 0;
}
