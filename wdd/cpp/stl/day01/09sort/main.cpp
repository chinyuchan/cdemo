#include <algorithm>
#include <iostream>
using namespace std;

template<typename T>
void swap_(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
void show(T arr[], size_t l) {
    for(int i=0; i < l; ++i) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

template<typename T>
bool less_(T a, T b) {
    return a < b;
}

template<typename T>
bool great_(T a, T b) {
    return a > b;
}

template<typename T>
class MyLess {
public:
    bool operator()(T a, T b) {
        return a < b;
    }
};

template<typename T>
class MyGreat {
public:
    bool operator()(T a, T b) {
        return a > b;
    }
};

template<typename T, typename C>
void sort_(T arr[], size_t n, C compare) {
    for (int i = 1; i < n; ++i) {
        bool swap = false;
        for (int j = 1; j <= n - i; ++j) {
            if (compare(arr[j], arr[j-1])) {
                swap_(arr[j], arr[j-1]);
                swap = true;
            }
        }

        if (!swap) {
            break;
        }
    }
}

template<typename T, typename C=MyLess<T>>
void sort2_(T arr[], size_t n, C compare=MyLess<T>()) {
    for (int i = 1; i < n; ++i) {
        bool swap = false;
        for (int j = 1; j <= n - i; ++j) {
            if (compare(arr[j], arr[j-1])) {
                swap_(arr[j], arr[j-1]);
                swap = true;
            }
        }

        if (!swap) {
            break;
        }
    }
}

int main()
{
    int arr[10] = {9, 7, 8, 5, 0, 1, 4, 3, 2, 6};
    sort_<int>(arr, 10, less_<int>);
    show(arr, 10);

    int arr2[10] = {9, 7, 8, 5, 0, 1, 4, 3, 2, 6};
    sort_<int>(arr2, 10, great_<int>);
    show(arr2, 10);

    int arr3[10] = {9, 7, 8, 5, 0, 1, 4, 3, 2, 6};
    sort2_<int>(arr3, 10);
    show(arr3, 10);

    int arr4[10] = {9, 7, 8, 5, 0, 1, 4, 3, 2, 6};
    sort_<int>(arr4, 10, MyGreat<int>());
    show(arr4, 10);

    return 0;
}
