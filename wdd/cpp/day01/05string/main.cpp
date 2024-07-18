#include <iostream>

int main() {
    std::string s = "Hello";
    std::cout << s << std::endl;
    s = "World";
    std::cout << s << std::endl;

    s[0] = 'X';
    std::cout << s << std::endl;

    std::string s1 = s;
    s1[0] = 'Y';
    std::cout << s << ", " << s1 << std::endl;

    // 构造方式
    std::string s2;
    std::string s3 = "Hello World!";
    std::string s4("Hello World!"); // 推荐
    std::string s5(s3);
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;
    std::cout << s5 << std::endl;

    s2 = s3;
    std::cout << s2 << std::endl;
    std::string s6 = s3 + s4;
    std::cout << s6 << std::endl;
    std::cout << s6.length() << std::endl;

    for (char ch: s6) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;

    return 0;
}
