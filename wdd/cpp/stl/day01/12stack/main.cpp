#include <iostream>
using namespace std;

template <typename T>
class Stack {
public:
    Stack(size_t cap) : _cap(cap), _size(0), _data(new T[cap]) {}

    Stack(const Stack& s) {
        _data = new T[s._cap];
        _size = s._size;
        _cap = s._cap;
        for (int i = 0;i < _size; ++i) {
            _data[i] = s._data[i];
        }
    }

    Stack& operator=(const Stack& s) {
        if (this != &s) {
            Stack tmp(s);
            swap(_data, tmp._data);
            swap(_size, tmp._size);
            swap(_cap, tmp._cap);
        }
        return *this;
    }

    ~Stack() {
        if (_data != nullptr) {
            delete[] _data;
            _data = nullptr;
        }
    }

    bool empty() const {
        return _size == 0;
    }

    bool full() const {
        return _size >= _cap;
    }

    size_t size() const {
        return _size;
    }

    void push(const T& data) {
        if (full()) {
            throw overflow_error("stack full");
        }
        _data[_size++] = data;
    }

    T pop() {
        if (empty()) {
            throw overflow_error("stack empty");
        }
        return _data[--_size];
    }
    T peek() {
        if (empty()) {
            throw overflow_error("stack empty");
        }
        return _data[_size-1];
    }

private:
    size_t _size;
    size_t _cap;
    T* _data;

};

void push(Stack<int>& s) {
    cout << "input:";
    int data = 0;
    cin >> data;
    try {
        s.push(data);
        cout << "push ok." << endl;
    }
    catch (overflow_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void pop(Stack<int>& s) {
    try {
        int data = s.pop();
        cout << "pop ok: " << data << endl;
    }
    catch (overflow_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void peek(Stack<int>& s) {
    try {
        int data = s.peek();
        cout << "top: " << data <<endl;
    }
    catch (overflow_error& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void menu() {
    cout << "-------------stack Test---------------------" << endl;
    cout << "[1] push" << endl;
    cout << "[2] pop" << endl;
    cout << "[3] peek" << endl;
    cout << "[0] exit" << endl;
}
int main() {
    Stack<int> s(3);
    while(true) {
        menu();
        int in = 0;
        cin >> in;
        switch(in) {
            case 0:
                return 0;
            case 1:
                push(s);
                break;
            case 2:
                pop(s);
                break;
            case 3:
                peek(s);
                break;
            default:
                cout << "Error" << endl;
        }
    }
    return 0;
}
