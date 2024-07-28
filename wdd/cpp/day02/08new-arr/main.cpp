#include <iostream>
using namespace std;

int main()
{
    int* pt =  new int[10];
    for (int i = 0; i < 10; ++i) {
        cout << *(pt+i) << ' ';
    }
    cout << endl;
    delete[] pt;

    pt = new int[]{1314, 1024, 9527, 8888, 6666, 5201314};
    for (int i = 0; i < 6; ++i) {
        cout << *(pt+i) << ' ';
    }
    cout << endl;
    delete pt;

    return 0;
}
