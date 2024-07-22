#include <iostream>

void fun(int a) {
    std::cout << "fun(int)" << std::endl;
}


int main() {
    fun(10);

    // 不完全匹配，对参数进行类型转换
    float a = 1.23;
    fun(a);
    char ch = 'a';
    fun(ch);

    return 0;
}
