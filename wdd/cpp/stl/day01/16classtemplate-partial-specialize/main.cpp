#include <iostream>
using namespace std;

template<typename T>
class A {
public:
    A() {
        cout << "class<T>" << endl;
    }
};

template<typename T>
class A<T*>{
public:
    A() {
        cout << "class<T*>" << endl;
    }
};

template<typename T>
class A<T[]>{
public:
    A() {
        cout << "class<T[]>" << endl;
    }
};

template<typename T, typename K, typename L>
class B {
public:
    B() {
        cout << "B<T,K,L>" << endl;
    }
};

template<typename T, typename K>
class B<T, K, K> {
public:
    B() {
        cout << "B<T,K,K>" << endl;
    }
};

template<typename T, typename K>
class B<T, T, K> {
public:
    B() {
        cout << "B<T,T,K>" << endl;
    }
};

template<typename T>
class B<T, T, T> {
public:
    B() {
        cout << "B<T,T,T>" << endl;
    }
};

int main()
{
    A<int> a1;
    A<int*> a2;
    A<int[]> a3;

    B<int, char, double> b1;
    B<int, char, char> b2;
    B<int, int, char> b3;
    B<int, int, int> b4;

    return 0;
}
