#include <iostream>
using namespace std;

class Array {
public:
    explicit Array(int size=10) : data(new int[size]), len(size) {
        cout << "Array()" << endl;
    }
    ~Array() {
        cout << "~Array()" << endl;
        if (data) {
            delete[] data;
            data = nullptr;
        }
    }
    int length() const { return len; }
    int& at(int index) { return data[index]; }
    void show() const {
        for (int i = 0; i < len; ++i) {
            cout << data[i] << ' ';
        }
        cout << endl;
    }
private:
    int len;
    int* data;
};

int main()
{
    Array arr;
    arr.show();
    cout << arr.length() << endl;

    return 0;
}
