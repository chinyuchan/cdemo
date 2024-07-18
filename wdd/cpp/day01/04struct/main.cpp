#include <iostream>

struct Empty {};

struct A {
    static int a;
};
int A::a = 100;
struct Human {
    char name[64];
    int age;
};

struct Student : Human {
    double score;
    void show() {
        std::cout << name << ", " << age << ", " << score << std::endl;
    }
};

int main() {
    std::cout << sizeof(Empty) << std::endl;

    std::cout << A::a << std::endl;

    Student s = {"Tom", 18, 88.5};
    s.show();

    return 0;
}
