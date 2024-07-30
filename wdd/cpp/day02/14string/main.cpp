#include <iostream>
using namespace std;


int main()
{
    string s;
    cout << s << endl;

    string s1 = "Hello"; // s1 = string("Hello");
    cout << s1 << endl;

    string s2("Hello"); // string s2{"hello"};
    cout << s2 << endl;

    string s3(s2);
    cout << s3 << endl;

    string s4 = s2;
    cout << s4 << endl;

    char str[100] = "Hello";
    string s5(&str[0], &str[5]); // 左闭右开区间
    cout << s5 << endl;

    string s6(10, 'c');
    cout << s6 << endl;

    cout << s1.length() << endl;
    string s7 = string("Hello") + string(" World");
    s7 = string("Hello") + " World";
    cout << s7 << endl;


    cout << s7[0] << endl;
    s7[0] = 'X';
    cout << s7 << endl;
    cout << s[100] << endl; // 越界不会报错

    s7.at(0) = 'Y';
    cout << s7 << endl;
    try {
        s7.at(100); // 越界不会抛出异常
    }
    catch(out_of_range& e) {
        cout << e.what() << endl;
    }

    for(int i = 0; i < s7.length(); ++i) {
        cout << s7.at(i);
    }
    cout << endl;
    for(const char& c: s7) {
        cout << c;
    }
    cout << endl;

    cout << s7.front() << endl;
    cout << s7.back() << endl;
    s7.front() = 'A';
    s7.back() = 'Z';
    cout << s7 << endl;

    const char* ps = s7.c_str();
    cout << ps << endl;
    cout << s7.data() << endl;
    cout << s7.empty() << endl; // 0
    cout << s.empty() << endl; // 1

    cout << s7.size() << endl;
    cout << s7.length() << endl;

    string s8("中国");
    cout << s8.size() << endl; // 6
    cout << s8.length() << endl; // 6
    cout << s8.max_size() << endl;
    cout << s8.capacity() << endl;
    s8.reserve(100);
    cout << s8.capacity() << endl;
    s8.shrink_to_fit();
    cout << s8.capacity() << endl;

    s8.clear();
    cout << s8 << endl;


    return 0;
}
