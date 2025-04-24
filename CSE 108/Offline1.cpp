#include <iostream>
#include <cmath>
using namespace std;


class Fraction
{
    int numerator;
    int denominator;

    int find_gcd(int a, int b)
    {
        if (b == 0) return a;
        return find_gcd(b, a % b);
    }

public:
    Fraction()
    {
        numerator = 0;
        denominator = 1;
    }

    Fraction(int num)
    {
        numerator = num;
        denominator = 1;
    }

    Fraction(int num, int denom)
    {
        if (denom == 0)
        {
            numerator = num;
            denominator = 1;
            cout << "Denominator cannot be 0" << endl;
            cout << "Denominator replaced by 1" << endl;
        }
        else
        {
            int gcd = find_gcd(num, denom);
            numerator = num / gcd;
            denominator = denom / gcd;
        }
    }

    Fraction add(Fraction &f)
    {
        int num = numerator*f.denominator + denominator*f.numerator;
        int denom = denominator*f.denominator;
        return Fraction(num, denom);
    }

    Fraction add(int n)
    {
        return Fraction(numerator + n*denominator, denominator);
    }

    Fraction sub(Fraction &f)
    {
        int num = numerator*f.denominator - denominator*f.numerator;
        int denom = denominator*f.denominator;
        return Fraction(num, denom);
    }

    Fraction sub(int n)
    {
        return Fraction(numerator - n*denominator, denominator);
    }

    Fraction mul(Fraction &f)
    {
        return Fraction(numerator*f.numerator, denominator*f.denominator);
    }

    Fraction mul(int n)
    {
        return Fraction(n*numerator, denominator);
    }

    Fraction div(Fraction &f)
    {
        if (f.numerator == 0)
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        else return Fraction(numerator*f.denominator, denominator*f.numerator);
    }

    Fraction div(int n)
    {
        if (n == 0)
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        else return Fraction(numerator, n*denominator);
    }

    void print()
    {
        cout << numerator << '/' << denominator << endl;
    }

    // ~Fraction();
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

/*
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
*/
    return 0; 
}