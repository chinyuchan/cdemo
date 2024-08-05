#include <iostream>
using namespace std;

class Book {
public:
    Book(int no, const string& name, const string& author, float price) {
        // 局部变量自赋值
        // no = no;

        this->no = no;
        this->name = name;
        this->author = author;
        this->price = price;
    }

    void info() const {
        cout << no << ' ' << name << ' ' << author << ' ' << price << endl;
    }

private:
    int no;
    string name;
    string author;
    float price;
};


int main() {
    Book b(1001, "C++", "本贾尼·斯特劳斯特卢普", 100.0);
    b.info();
    return 0;
}
