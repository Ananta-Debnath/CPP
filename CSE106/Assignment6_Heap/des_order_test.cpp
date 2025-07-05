#include <iostream>
#include <fstream>
#include <cstdio>
#include <queue>
#include <ctime>

using namespace std;


int main()
{
    //reading from file begins. Loading all the numbers in the vector
    string myText;
    ifstream MyReadFile("out.txt");
    getline (MyReadFile, myText);
    int m = atoi(myText.c_str());
    int n, i = 0;
    while (getline (MyReadFile, myText))
    {
        n = atoi(myText.c_str());
        // cout << i << ": " << m << " -- " << n << endl;
        if (m < n)
        {
            cout << i << ": " << m << " -- " << n << endl;
            MyReadFile.close();
            break;
        }
        m = n;
        i++;
    }
    cout << "All OK" << endl;
    MyReadFile.close();
    //reading from file ends
}