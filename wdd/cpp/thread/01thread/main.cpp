#include <iostream>
#include <thread>
using namespace std;

void func() {
    for(char ch='A'; ch <= 'Z'; ++ch) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void func2() {
    for(char ch='a'; ch <= 'z'; ++ch) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}

void func3() {
    for(char ch='0'; ch <= '9'; ++ch) {
        cout << ch;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
}


int main() {
    thread t1(func);
    thread t2(func2);
    thread t3(func3);

    thread t4([](const int x, const int y)-> void {
        cout << x << ' ' << y << endl;
        for (int i = 0; i < 10; ++i) {
            cout << '@';
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    }, 123, 456);

    //thread t5(t4);//不支持拷贝构造
    thread t5(move(t4));

    t1.join();
    t2.join();
    t3.join();
    //t4.join(); // 移动后无效
    t5.join();

    return 0;
}
