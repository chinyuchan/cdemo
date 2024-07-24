#include <iostream>

template<typename T>
T max_(T a, T b) {
    return a > b ? a : b;
}

int main()
{
    // 函数模板实例化
    // 用具体的类型实例化模板，得到一个具体的函数：int max_(int,int)
    std::cout << max_(1, 2) << std::endl;
    // 隐式推导类型
    std::cout << max_(1.23, 4.56) << std::endl;
    // 显式指定类型
    std::cout << max_<char>('8', 'a') << std::endl;

    // std::cout << max_(3, 4.56) << std::endl;
    std::cout << max_<double>(3, 4.56) << std::endl;
    return 0;
}
