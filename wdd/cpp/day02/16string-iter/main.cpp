#include <cstring>
#include <iostream>
using namespace std;

int main() {
    string s("thank you");
    for(const char& c : s) {
        cout << c;
    }
    cout << endl;

    string::iterator it = s.begin();
    for(; it != s.end(); ++it) {
        cout << *it;
    }
    cout << endl;

    string::reverse_iterator rit = s.rbegin();
    for(; rit != s.rend(); ++rit) {
        cout << *rit;
    }
    cout << endl;

    char str[100] = "thank you";
    size_t len = strlen(str);
    char* ps = &str[0];
    for (; ps != str + len; ++ps) {
        cout << *ps;
    }
    cout << endl;

    return 0;
}
