#include <iostream>
using namespace std;


class Fraction
{
    int numerator;
    int denominator;

public:
    Fraction();

    Fraction(int denom);

    Fraction(int num, int denom);

    Fraction add(Fraction &f);

    Fraction add(int n);

    Fraction sub(Fraction &f);

    Fraction sub(int n);

    Fraction mul(Fraction &f);

    Fraction mul(int n);

    Fraction div(Fraction &f);

    Fraction div(int n);

    void print();

    ~Fraction();
};


class FractionCollection
{
    Fraction *fractions;
    int maxlength;
    int length;

public:
    FractionCollection();

    FractionCollection(int size);

    void insert(Fraction f);

    void insert(int pos, Fraction f);

    void remove();

    void remove(Fraction f);

    void remove(int pos);

    Fraction getmax();

    Fraction getmin();

    Fraction add(int start, int end);

    Fraction mul(int start, int end);

    Fraction sub(int pos1, int pos2);

    Fraction div(int pos1, int pos2);

    void print();

    ~FractionCollection();
};


int main()
{ // create Fraction with numerator, denominator
    Fraction a(5, 2), b(7, 2), c(9, 2), d(28, 5);
    cout << "Fraction" << endl;
    cout << "-------------------------------" << endl;
    cout << "A: ";
    a.print();
    cout << "B: ";
    b.print();
    cout << endl;

    cout << "Add(a,b): ";
    a.add(b).print();
    cout << "Add(a,2): ";
    a.add(2).print();

    cout << "Sub(a,b) ";
    a.sub(b).print();
    cout << "Sub(a,2) ";
    a.sub(2).print();

    cout << "Mul(a,b): ";
    a.mul(b).print();
    cout << "Mul(a,2): ";
    a.mul(2).print();

    cout << "Div(a,b): ";
    a.div(b).print();
    cout << "Div(a,2): ";
    a.div(2).print();
    cout << "Div(a,0): ";
    a.div(0).print();


    // Collection of Fractions
    Fraction e, f(5), g(10);
    FractionCollection fc(10);
    fc.insert(a);
    fc.insert(b);
    fc.insert(c);
    fc.print();

    cout << "Sub(Pos0, Pos1): ";
    fc.sub(0, 1).print(); // subtracts the fraction at pos1 from fraction at pos0
    cout << "Div(Pos0, Pos1): ";
    fc.div(0, 1).print(); // divides the fraction at pos0 by the fraction at pos1

    fc.remove(1);         // removed 'b'
    fc.print();

    fc.remove(a);
    fc.print();

    fc.insert(d);
    fc.insert(0, e); // insert at pos0
    fc.insert(f);
    fc.insert(g);
    fc.print();

    fc.remove(); // removed the last fraction
    fc.print();  // notice the output

    return 0; 
}