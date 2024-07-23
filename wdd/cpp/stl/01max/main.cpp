#include <iostream>

int max_(int a, int b) {
    return a > b ? a : b;
}

double max_(double a, double b) {
    return a > b ? a : b;
}

char max_(char a, char b) {
    return a > b ? a : b;
}


int main()
{
    std::cout << max_(1,2) << std::endl;
    std::cout << max_(1.2, 3.4) << std::endl;
    std::cout << max_('1', '8') << std::endl;
    return 0;
}
