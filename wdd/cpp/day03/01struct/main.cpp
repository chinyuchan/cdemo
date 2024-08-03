#include <iostream>
using namespace std;

struct Book {
    int no;
    string name;
    string author;
    float price;

    void info() {
        cout <<no << ' ' << name << ' ' <<author << ' ' << price << endl;
    }
};

void show_book_info(Book* book) {
    cout << book->no << ' ' << book->name << ' ' << book->author << ' ' << book->price << endl;
}

int main()
{
    Book b = {1001, "C++", "本贾尼·斯特劳斯特卢普", 99.9};
    //show_book_info(&b);
    b.info();

    Book b2 = {1002, "Java", "詹姆斯·高斯林", 98.9};
    b2.info();

    Book b3;
    b3.info();

    return 0;
}
