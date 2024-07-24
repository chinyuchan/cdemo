#include <iostream>
using namespace std;

template<typename T=int, size_t N=10>
void func() {
    T data[N]{};
    cout << typeid(T).name() << endl;
    cout << N << endl;
}

int main()
{
    func();
    func<>();
    func<char>();
    func<double, 20>();

    return 0;
}
