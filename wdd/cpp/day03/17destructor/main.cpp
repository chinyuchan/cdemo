#include <iostream>
using namespace std;
class File {
public:
    File(const char* filename, const char* mode) {
        fp = fopen(filename, mode);
    }
    ~File() {
        cout << "~File()" << endl;
        if (fp) {
            fclose(fp);
            fp = nullptr;
        }
    }
    void write(const string& s) {
        fwrite(s.c_str(), 1, s.size(), fp);
    }

    void read(char s[], size_t n) {
        fread(s, 1, n, fp);
    }

    void close() {
        fclose(fp);
        fp = nullptr;
    }

private:
    FILE* fp;
};

int main()
{
    File f("a.txt", "w");
    f.write(string("hello"));
    //f.close();

    return 0;
}
