#include <iostream>
using namespace std;

int main() {
    int a = 1024;
    int& ra = a;
    cout << ra << endl;
    ra = 9527;
    cout << a << endl;

    cout << &a << endl;
    cout << &ra << endl;


    return 0;
}
