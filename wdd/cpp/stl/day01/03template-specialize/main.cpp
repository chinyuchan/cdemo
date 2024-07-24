#include <cstring>
#include <iostream>
#include <typeinfo>

template<typename T>
T max_(T a, T b) {
    std::cout << typeid(T).name() << std::endl;
    return a > b ? a : b;
}

//对于某些类型，模板并不适用。
const char* max_(const char* a, const char* b) {
    std::cout << "针对const char*特殊处理" << std::endl;
    return strcmp(a, b) > 0 ? a : b;
}

int main()
{
    // 调用普通版本
    std::cout << max_("abc", "xyz") << std::endl;
    // 指定调用模板函数
    std::cout << max_<const char*>("abc", "xyz") << std::endl;

    return 0;
}
