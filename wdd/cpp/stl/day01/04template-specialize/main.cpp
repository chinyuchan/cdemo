#include <cstring>
#include <iostream>
#include <typeinfo>

template<typename T>
T max_(T a, T b) {
    std::cout << typeid(T).name() << std::endl;
    return a > b ? a : b;
}

// 针对特定类型的函数模板
template<>
const char* max_<const char*>(const char* a, const char* b) {
    std::cout << "针对const char*特殊处理" << std::endl;
    return strcmp(a, b) > 0 ? a : b;
}

int main()
{
    std::cout << max_("abc", "xyz") << std::endl;
    std::cout << max_<const char*>("abc", "xyz") << std::endl;

    return 0;
}
