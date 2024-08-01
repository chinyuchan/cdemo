#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Stack : public vector<T> {
public:
    // 域作用符表示调用父类的函数
    bool empty() { return vector<T>::empty(); }
    size_t size() const { return vector<T>::size(); }
    void push(const T& data) { vector<T>::push_back(data); }

    T pop() {
        if (empty()) {
            throw underflow_error("Stack empty");
        }
        //T data = this->operator[](size() -1);
        T data = vector<T>::back();
        vector<T>::pop_back();
        return data;
    }

    T peek() {
        if (empty()) {
            throw
             underflow_error("Stack empty");
        }
        return vector<T>::back();
    }
};

template<typename T>
void print_stack(Stack<T>& s) {
    cout << "stack: ";
    for(auto n : s) {
        cout << n << ' ';
    }
    cout << endl;
}

int main()
{
    Stack<int> s;
    cout << "empty: " << boolalpha << s.empty() << endl;
    s.push(1);
    s.push(2);
    s.push(3);
    print_stack(s);
    cout << "pop: " << s.pop() << endl;
    cout << "pop: " << s.pop() << endl;
    print_stack(s);
    cout << "pop: " << s.pop() << endl;
    print_stack(s);
    cout << "empty: " << boolalpha << s.empty() << endl;
    return 0;
}
