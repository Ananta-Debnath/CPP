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
    
    ObAssign &operator=(const ObAssign &obj)
    {
        if (this == &obj)
        {
            return *this; // self-assignment
        }
        cout << str << endl;
        free(str);
        len = obj.len;
        str = (char *)malloc(len + 1);
        strcpy(str, obj.str);
        return *this;
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
    ObAssign ob1("Hello World");
    ObAssign ob2("Learning C++");

    ob1.show();
    ob2.show();

    ob2 = ob1; // Assignment operator is invoked
    ob2.show();

    return 0;
}
