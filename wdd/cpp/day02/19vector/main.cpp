#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b) {
    return a > b;
}

int main() {
    // 个数(size)相等且相同位置的元素也相等，则两向量相等
    vector<int> v1{1,2,3};
    vector<int> v2{1,2,3};
    cout << (v1 == v2) << endl;

    v2.reserve(10);
    cout << (v1 == v2) << endl;

    v2.resize(10);
    cout << (v1 == v2) << endl;

    v2[0] =2;
    cout << (v1 == v2) << endl;

    vector<int> v3{5, 9, 1, 0, 4, 8, 7, 2, 6, 3};
    //sort(v3.begin(), v3.end(), cmp);
    //sort(v3.begin(), v3.end(), greater<int>());
    sort(v3.begin(), v3.end(), less<int>());

    for(auto n : v3) {
        cout << n << ' ';
    }
    cout << endl;

    return 0;
}
