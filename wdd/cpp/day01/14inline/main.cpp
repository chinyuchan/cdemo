#include <iostream>
using namespace std;

inline int feibo(int x) {
    if (x <= 2) {
        return 1;
    }
    return feibo(x-1) + feibo(x-2);
}


int main()
{
    cout << feibo(10) << endl;

    return 0;
}
