#include <iostream>
using namespace std;

template<typename T, size_t L=10>
class Array {
public:
    T& operator[](size_t index) {
        return arr[index];
    }
    const T& operator[](size_t index) const {
        return arr[index];
    }
    size_t size() const {
        return L;
    }

private:
    T arr[L];
};

int main() {
    Array<int> arr{};

    for (int i=0; i < arr.size(); ++i) {
        arr[i] = i * 10;
    }
    for(int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}
