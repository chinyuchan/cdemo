#include <iostream>
#include <cstring>
using namespace std;

template<typename T>
class Compare {
public:
    Compare(const T& first, const T& second) : _first(first), _second(second) {}
    T first() const { return _first; }
    T second() const { return _second; }
    T max() const { return _first > _second ? _first : _second; }
    T min() const { return _first < _second ? _first : _second; }

private:
    T _first;
    T _second;
};

//全员特化
template<>
class Compare<const char*> {
public:
    Compare(const char* first, const char* second) : _first(first), _second(second) {}
    const char* first() const { return _first; }
    const char* second() const { return _second; }
    const char* max() const { return strcmp(_first, _second) > 0 ? _first : _second; }
    const char* min() const { return strcmp(_first, _second) < 0 ? _first : _second; }

private:
    const char* _first;
    const char* _second;
};

// 成员特化
template<>
char* Compare<char*>::max() const {
    return strcmp(_first, _second) > 0 ? _first : _second;
}

template<>
char* Compare<char*>::min() const {
    return strcmp(_first, _second) < 0 ? _first : _second;
}

int main()
{
    Compare<int> cmp(1024, 9547);
    cout << cmp.max() << endl;
    cout << cmp.min() << endl;

    Compare<const char*> cmp2("hello", "world");
    cout << "max=" << cmp2.max() << endl;
    cout << "min=" << cmp2.min() << endl;

    char s1[] = "abc";
    char s2[] = "xyz";
    Compare<char*> cmp3(s1, s2);
    cout << "max=" << cmp3.max() << endl;
    cout << "min=" << cmp3.min() << endl;
    return 0;
}
