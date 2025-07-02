#include <iostream>
#include "ArrayList.hpp"
using namespace std;

int main()
{
    ArrayList<int>* arr = new ArrayList<int>();

    for (int i = 0; i < 10; i++)
    {
        arr->add(i*3);
    }
    
    for (int x : *arr) cout << x << " ";
    cout << endl;

    for (int i = 0; i < 10; i++)
    {
        arr->remove(i);
    }

    for (int x : *arr) cout << x << " ";
    cout << endl;

    cout << (*arr)[2] << endl;
    (*arr)[2] = 1;
    cout << (*arr)[2] << endl;
}