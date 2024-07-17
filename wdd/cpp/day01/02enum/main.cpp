#include <iostream>

enum Direction{Left, Right, Up, Down};

int main() {
    std::cout << "sizeof(Direction) = " << sizeof(Direction) << std::endl;
    Direction d = Left;
    // d = 1; // Error
    std::cout << d << std::endl;

    int a = 0;
    a = Right;
    std::cout << a << std::endl;

    return 0;
}
