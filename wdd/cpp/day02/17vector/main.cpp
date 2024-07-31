#include <iostream>
#include <vector>
using namespace std;

struct Date {
    int year;
    int mon;
    int day;
};

int main()
{
    vector<int> v;
    vector<double> v1;
    vector<string> v2;
    vector<Date> v3;

    cout << v.size() << endl;
    v.resize(10);
    cout << v.size() << endl;
    for(int n: v) {
        cout << n << ' ';
    }
    cout << endl;
    cout << v.capacity() << endl;
    v.reserve(20);
    cout << v.capacity() << endl;

    v.push_back(1024);
    cout << v.size() << endl;
    cout << v.capacity() << endl;

    return 0;
}
