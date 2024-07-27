#include <iostream>
#include <cstdlib>
using namespace std;

int g = 10;

int& func() {
    int a = 1024;
    // return a; // ERROR
    static int b = 1024;
    //return b; // OK
    //return g; // OK
    int* p = (int*)malloc(sizeof(int));
    *p = 1024;
    return *p;
}


int main()
{
    int& ra = func();
    cout << ra << endl;

    return 0;
}
