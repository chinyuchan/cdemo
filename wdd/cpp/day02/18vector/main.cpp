#include <iostream>
#include <vector>
using namespace std;


int main() {
    vector<int> v;
    vector<int> v1(10);
    for(int n: v1) {
        cout << n << ' ';
    }
    cout << endl;

    vector<int> v2(10, 1314);
    for(int n: v2) {
        cout << n << ' ';
    }
    cout << endl;

    vector<int> v3(v2);
    for(int n: v3) {
        cout << n << ' ';
    }
    cout << endl;

    vector<int> v4{1, 2, 3, 4, 5};
    for(int n: v4) {
        cout << n << ' ';
    }
    cout << endl;

    int arr[] = {6, 7, 8, 9, 10};
    vector<int> v5(&arr[0], &arr[5]);
    for(int n: v5) {
        cout << n << ' ';
    }
    cout << endl;

    vector<int> v6(v5.begin(), v5.begin()+5);
    for(int n: v6) {
        cout << n << ' ';
    }
    cout << endl;

    vector<int> v7(v5.begin(), v5.end());
    for(int n: v7) {
        cout << n << ' ';
    }
    cout << endl;

    v6.insert(v6.begin(), 5, 9999);
    v6.insert(v6.begin(), v5.begin(), v5.end());
    v6.insert(v6.begin(), {7, 7, 7, 7});
    for (int n : v6) {
        cout << n << ' ';
    }
    cout << endl;

    for(auto it = v6.begin(); it != v6.end();) {
        if (*it == 7) {
            it = v6.erase(it);
        }
        else {
            ++it;
        }
    }
    for (int n : v6) {
        cout << n << ' ';
    }
    cout << endl;

    for(auto it = v6.begin(); it != v6.end();) {
        if (*it == 9999) {
            it = v6.erase(it);
        }
        else {
            ++it;
        }
    }
    for (int n : v6) {
        cout << n << ' ';
    }
    cout << endl;

    return 0;
}
