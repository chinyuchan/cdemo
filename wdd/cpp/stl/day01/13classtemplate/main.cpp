#include <iostream>
using namespace std;

template<typename T>
class Compare {
public:
    Compare(const T& a, const T& b):_a(a),_b(b){}
    T max() const {
        return _a > _b ? _a : _b;
    }
    T min() const {
        return _a > _b ? _b : _a;
    }
private:
    T _a;
    T _b;
};

int main() {
    Compare cmp(10,20);
    cout << cmp.max() << endl;
    cout << cmp.min() << endl;

    Compare<int> cmp2(1,2);
    cout << cmp2.max() << endl;
    cout << cmp2.min() << endl;

    Compare cmp3(1.23,4.56);
    cout << cmp3.max() << endl;
    cout << cmp3.min() << endl;

    return 0;
}
