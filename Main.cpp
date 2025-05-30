#include <iostream>
using namespace std;

int funct(int *ptr)
{
    *ptr = *ptr + 10;
    return *ptr;
}

class Student
{
    int roll;

public:
    Student(int r) { roll = r; };
    void funct() const
    {
        (const_cast<Student *>(this))->roll = 5;
    }
    int getRoll() const { return roll; }
};

int main()
{
    const int num = 10;
    const int *ptr1 = &num;
    int *ptr2 = const_cast<int *>(ptr1);
    cout << "Value of num after: " << funct(ptr2) << endl;
    cout << "*ptr1: " << *ptr1 << endl;
    cout << "Value of num before: " << num << endl;
    // int val= const_cast<int>(num);
    Student std(3);
    cout << "Roll number before: " << std.getRoll() << endl;
    std.funct();
    cout << "Roll number after: " << std.getRoll() << endl;


    cout << (-1) % 5 << endl;



    return 0;
}