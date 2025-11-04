#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;


ostream& setup(ostream& os)
{
    os << fixed << hex << setprecision(3) << setw(10) << left << setfill('%');
    return os;
}

int main()
{
    ifstream in("src.txt", ios::binary);
    if (!in) cout << "cannot open" << endl;

    ofstream out("dst.txt");
    if (!out) cout << "out error" << endl;

    char c;
    in.get(c);
    cout << in.gcount() << endl;

    while(in.get(c))
    {
        out << c;
    }

    cout << in.gcount() << endl;
    in.close();
    out.close();
}