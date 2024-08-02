#include "list.h"

class Show {
public:
    void operator()(const int& n) {
        cout << n << ' ';
    }
};


int main() {
    List<int> l1;

    int arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    List<int> l2(&arr[0], &arr[10]);

    l2.push_back(110);
    l2.push_front(120);
    // l2.print([](const int& a) {
    //     cout << a << endl;
    // });
    l2.print(Show());

    return 0;
}
