#include <iostream>
using namespace std;

namespace n1 {
    int a = 1;
    namespace n2 {
        int b = 2;
        namespace n3 {
            int c = 3;
        }
    }
}

int main()
{
    cout << n1::a << endl;
    cout << n1::n2::b << endl;
    cout << n1::n2::n3::c << endl;

    using namespace n1;
    cout << a << endl;
    cout << n2::b << endl;
    cout << n2::n3::c << endl;

    using namespace n2;
    cout << a << endl;
    cout << b << endl;
    cout << n3::c << endl;

    using namespace n3;
    cout << a << endl;
    cout << b << endl;
    cout << c << endl;

    return 0;
}
