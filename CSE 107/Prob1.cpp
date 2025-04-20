#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class ObAssign
{
    char *str;
    int len;

public:
    ObAssign(char *s)
    {
        len = strlen(s);
        str = (char *)malloc(len + 1);
        strcpy(str, s);
    }
    ~ObAssign()
    {
        cout << "Freeing memory" << endl;
        free(str);
    }
    void show()
    {
        cout << str << ":" << len << endl;
    }
};

int main()
{
    ObAssign *ob1 = new ObAssign("Hello World");
    ObAssign *ob2 = new ObAssign("Like C++");

    ob1->show();
    ob2->show();
    ob2 = ob1;
    ob2->show();

    ob1->~ObAssign();

    return 0;
}