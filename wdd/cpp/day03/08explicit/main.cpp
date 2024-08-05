#include <iostream>
using namespace std;

class Student {
public:
    Student() : _no(0), _name(string("")), _gender(string("")), _score(0) {}
    explicit Student(int no) : _no(no) {
        cout << "Student(int)" << endl;
    }
    explicit Student(const string& name) : _name(name) {
        cout << "Student(string)" << endl;
    }
private:
    int _no{};
    string _name;
    string _gender;
    int _score{};
};


int main() {
    Student s;
    // 单参构造函数：参数可以隐式调用，构造成类对象
    // 可以使用explicit关键字方式这种隐式调用
    // s = 100; // Student(100);
    // s = string("add"); // Student("add");
    s = Student(100);
    s = Student("add");

    return 0;
}
