#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class List {
public:
    List() : _head(nullptr), _tail(nullptr) {}

    template<typename IT>
    List(IT beg, IT end) : _head(nullptr), _tail(nullptr) {
        for(; beg !=end; ++beg) {
            push_back(*beg);
        }
    }

    template<typename C>
    explicit List(const C& container) : _head(nullptr), _tail(nullptr) {
        for(const C& data: container) {
            push_back(data);
        }
    }

    List(const List& list) {
        for(Node* node = list._head; node!=nullptr; node= node->_next) {
            push_back(node->data);
        }
    }

    List& operator=(const List& list) {
        if (this != &list) {
            List l(list);
            swap(_head, l._head);
            swap(_tail, l._tail);
        }
        return *this;
    }

    List(List&& list) noexcept {
        _head = list._head;
        _tail = list._tail;
        list._head = nullptr;
        list._tail = nullptr;
    }

    List& operator=(List&& list) noexcept {
        if (this != &list) {
            clear();
            _head = list._head;
            _tail = list._tail;
            list._head = nullptr;
            list._tail = nullptr;
        }
        return *this;
    }

    ~List() {
        clear();
    }

    void push_back(const T& data) {
        Node* node = new Node(data, nullptr, _tail);
        if (_tail != nullptr) {
            _tail->_next = node;
        }
        else {
            _head = node;
        }

        _tail = node;
    }

    void clear() {
        for(Node* node; _head != nullptr;) {
            node = _head;
            _head = _head->_next;
            delete node;
        }
        _tail = nullptr;
    }

    [[nodiscard]] bool empty() const { return _head == nullptr && _tail == nullptr; }

    [[nodiscard]] size_t size() const {
        size_t cnt = 0;
        for(Node* node = _head; node != nullptr; node = node->_next) {
            ++cnt;
        }
        return cnt;
    }

    void push_front(const T& data) {
        Node* node = new Node(data, _head, nullptr);
        if (_head != nullptr) {
            _head->_prev = node;
        }
        else {
            _tail = node;
        }
        _head = node;
    }

    void pop_front() {
        if (empty()) {
            throw underflow_error("empty");
        }
        else {
            Node* node = _head;
            _head = _head->_next;
            if (_head ==nullptr) {
                _tail = nullptr;
            }
            delete node;
        }
    }

    void pop_back() {
        if (empty()) {
            throw underflow_error("empty");
        }
        else {
            Node* node = _tail;
            _tail = _tail->_prev;
            if (_tail == nullptr) {
                _head = nullptr;
            }
            delete node;
        }
    }

    T& front() {
        if (empty()) {
            throw underflow_error("empty");
        }
        else {
            return _head->data;
        }
    }

    const T& front() const {
        if (empty()) {
            throw underflow_error("empty");
        }
        else {
            return _head->data;
        }
    }

    T& back() {
        if (empty()) {
            throw underflow_error("empty");
        }
        else {
            return _tail->data;
        }
    }

    const T& back() const {
        if (empty()) {
            throw underflow_error("empty");
        }
        else {
            return _tail->data;
        }
    }

    template<typename F>
    void print(F f) {
        for(Node* node = _head; node != nullptr; node = node->_next) {
            f(node->_data);
        }
    }

private:
    class Node {
    public:
        explicit Node(const T& data, Node* next=nullptr, Node* prev=nullptr) : _data(data), _next(next), _prev(prev) {}
        Node() : _next(nullptr), _prev(nullptr) {}

        T _data;
        Node* _next;
        Node* _prev;
    };

    Node* _head;
    Node* _tail;
};



#endif //LIST_H
