#include <iostream>
using namespace std;

class Book {
public:
    Book(const int no, const string& name, const string& author, const float price)
        :
        _no(no),
        _name(name),
        _author(author),
        _price(price)
    {
        cout << "constructor" << endl;
    }

    //无参构造函数
    Book()
        :
        _no(0),
        _name(string("")),
        _author(string("")),
        _price(0.0)
    {
        cout << "constructor" << endl;
    }

    // 单参构造函数
    Book(int no)
        :
        _no(no),
        _name(string("")),
        _author(string("")),
        _price(0.0)
    {
        cout << "constructor" << endl;
    }

    void info() {
        cout << _no << ' ' << _name << ' ' << _author << ' ' << _price << endl;
    }

private:
    int _no;
    string _name;
    string _author;
    float _price;
};


int main()
{
    Book b(1001, "C++", "本贾尼·斯特劳斯特卢普", 99.9);
    b.info();

    Book b2(1002, "Java", "詹姆斯·高斯林", 98.9);
    b2.info();

    Book b3;
    b3.info();

    Book b4(1003);
    b4.info();

    return 0;
}
