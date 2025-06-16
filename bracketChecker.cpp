#include <stack>
#include <iostream>
using namespace std;

bool isValidCombo(string a)
{
    stack<char> A;
    int i = 0;
    bool combo = true;

    while (a[i] != '\0')
    {
        if (a[i] == '(' || a[i] == '{' || a[i] == '[')
        {
            A.push(a[i]);
        }
        else if (a[i] == ')' || a[i] == '}' || a[i] == ']')
        {            
            if (A.empty())
            {
                combo = false;
                break;
            }

            char top = A.top();

            if ((top == '(' && a[i] == ')') ||
                (top == '{' && a[i] == '}') ||
                (top == '[' && a[i] == ']'))
            {
                A.pop();
            }
            else
            {
                combo = false;
                break;
            }
        }

        i++;
    }

    return combo && A.empty();
}

int main()
{
    string a;
    // cin >> a;
    getline(cin, a);

    if (isValidCombo(a))
    {
        cout << "VALID COMBO" << endl;
    }
    else
    {
        cout << "NOT" << endl;
    }
}