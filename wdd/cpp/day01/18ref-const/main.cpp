#include <iostream>
using namespace std;

void func(int arr[]) {}

void func(int(&arr)[5]) {}

int main()
{
    const char* ps1 = "hello";
    char const* ps2 = "hello";

    char s[100] = "hello";
    char s2[100] = "world";
    char* const ps3 = s;
    // ps3 = s2; // ERROR

    const int a = 1024;
    const int& ra = a;
    int const& rb = a;

    // int& const rc = a; // ERROR

    int arr[5]{1,2,3,4,5};
    int(&rarr)[5] = arr;
    for(auto n: rarr) {
        cout << n << ' ';
    }
    cout << endl;

    return 0;
}
