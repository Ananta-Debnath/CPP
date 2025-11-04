#include <iostream>
using namespace std;


template<typename T, int N = 1>
class myclass
{
private:
    T x;

public:
    myclass(T t)
    {
        x = t * N;
    }

    T getx()
    {
        return x;
    }
};


int main()
{
    myclass<double> d1(1.1);
    myclass<double, 2> d2(1.1);
    myclass<double, 3> d3(1.1);
    cout << d1.getx() << " " << d2.getx() << " " << d3.getx() << "\n";
    myclass<int, 4> i1(5);
    myclass<int> i2(5);
    cout << i1.getx() << " " << i2.getx();
    return 0;
}