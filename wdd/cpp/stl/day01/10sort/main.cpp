#include <iostream>
using namespace std;

template<typename IT>
void show(IT beg, IT end) {
    for(; beg != end; ++beg) {
        cout << *beg << ' ';
    }
    cout << endl;
}

template<typename T, typename C = less<T>>
void sort_(T* beg, T* end, C cmp=less<T>()) {
    T* last = end;
    for (T* s = beg; s != end; ++s) {
        bool sp = false;
        for(T* cur = beg + 1; cur != last; ++cur) {
            if (cmp(*cur, *(cur-1))) {
                swap(*cur, *(cur-1));
                sp = true;
            }
        }

        if (!sp) {
            break;
        }

        --last;
    }
}


int main() {
    int arr[10] = {9, 7, 8, 5, 0, 1, 4, 3, 2, 6};
    sort_(&arr[0], &arr[10]);
    show(&arr[0], &arr[10]);

    int arr2[10] = {9, 7, 8, 5, 0, 1, 4, 3, 2, 6};
    sort_(&arr2[0], &arr2[10], greater<int>());
    show(&arr2[0], &arr2[10]);

    return 0;
}
