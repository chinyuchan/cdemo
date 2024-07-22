#include <iostream>

int sum(int a, int b) {
    return a + b;
}

double sum(double a, double b) {
    return a + b;
}

void fun() {
    std::cout << "fun()" << std::endl;
}

void fun(int a) {
    std::cout << "fun(int)" << std::endl;
}

void fun(double a) {
    std::cout << "fun(double)" << std::endl;
}

void f1(int a, double b) {
    std::cout << "f1(int, double)" << std::endl;
}

void f1(double a ,int b) {
    std::cout << "f1(double, int)" << std::endl;
}

void f2(int* p) {
    std::cout << "f2(int*)" << std::endl;
}

void f2(const int* p) {
    std::cout << "f2(const int*)" << std::endl;
}

void f3(int& a) {
    std::cout << "f3(int&)" << std::endl;
}

void f3(const int& a) {
    std::cout << "f3(const int&)" << std::endl;
}

int main() {
    std::cout << sum(1024, 9527) << std::endl;
    std::cout << sum(1.23, 4.56) << std::endl;

    fun();
    fun(1);
    fun(1.23);
    f1(1, 2.34);
    f1(1.23, 4);

    int a;
    const int b = 10;
    f2(&a);
    f2(&b);

    int& ra = a;
    const int& rb = b;
    f3(ra);
    f3(rb);

    return 0;
}
