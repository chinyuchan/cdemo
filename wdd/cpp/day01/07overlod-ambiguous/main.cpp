#include <iostream>

void fun(int a, int b) {
    std::cout << "fun(int, int)" << std::endl;
}

void fun(double a, double b) {
    std::cout << "fun(double, double)" << std::endl;
}

int main() {
    fun(1, 2);
    fun(1.23, 4.56);
    // fun(1.23, 4); // ERROR

    // 隐式转换
    float a = 1, b = 2;
    // float转double不会有数据损失，float转int会由数据损失
    fun(a, b);
    fun('a', 'b');
    return 0;
}
