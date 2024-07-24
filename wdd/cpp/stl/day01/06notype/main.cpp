#include <iostream>
using namespace std;

template <typename T, size_t L>
void fun() {
    T data[L];
    for (int i = 0; i < L; ++i) {
        data[i] = i * 10;
    }
    for (auto n: data) {
        cout << n << ' ';
    }
    cout << endl;
}

int main() {
    fun<int, 10>();

    int a = 10;
    // fun<int, a>(); // ERROR

    const int b = 10; // OK
    fun<int, b>();

    constexpr int c = 10 + 10;
    fun<int, c>();

    return 0;
}
