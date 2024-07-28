#include <iostream>
using namespace std;

int main()
{
    double* pd = new double(3.14);
    cout << *pd << endl;
    cout << pd << endl;
    delete pd;

    pd = (double*)malloc(sizeof(double));
    cout << pd << endl;
    free(pd);

    return 0;
}
