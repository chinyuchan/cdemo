#include <iostream>
#include <cstdlib>
using namespace std;


struct Student {
    Student() {
        cout << "Student()" << endl;
    }
    ~Student() {
        cout << "~Student()" << endl;
    }
};

int main()
{
    Student* ps = (Student*)malloc(sizeof(Student));
    free(ps);

    ps = new Student;
    delete ps;

    return 0;
}
