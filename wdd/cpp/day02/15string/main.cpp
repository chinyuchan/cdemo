#include <iostream>
using namespace std;


int main()
{
    string s("hello");

    // 在3位置插入5个x
    s.insert(3, 5, 'x');
    cout << s << endl;

    //在0位置插入world字符串
    s.insert(0, "world");
    cout << s << endl;

    // 在0位置插入thank的前3个字符
    s.insert(0,"thank", 3);
    cout << s << endl;

    s.insert(s.begin()+3, 'm');
    cout << s << endl;
    char str[100] = "Hello, World!";
    s.insert(s.begin(), &str[0], &str[10]);
    cout << s << endl;

    // 从6位置，删除1个字符
    s.erase(6, 1);
    cout << s << endl;

    s.push_back('X');
    s.push_back('Y');
    s.push_back('Z');
    cout << s << endl;
    s.pop_back();
    cout << s << endl;
    s.append("XABC");
    cout << s << endl;

    string s1("hello world");
    string s2("hello world");
    string s3("world hello");
    cout << (s1 == s2) << endl;
    cout << (s1 == s3) << endl;
    // 0: 相等
    // < 0: 小于
    // > 0: 大于
    cout << s1.compare(s2) << endl;
    cout << s1.compare(s3) << endl;
    cout << s3.compare(s1) << endl;

    s1.replace(5,3,"abcdef");
    cout << s1 << endl;
    s.replace(s.begin(), s.begin()+3, "thank ");
    cout << s1 << endl;
    cout << s1.substr(0, 5) << endl;

    return 0;
}
