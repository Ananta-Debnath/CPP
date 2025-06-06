#include <iostream>
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
            numerator = num;
            denominator = denom;
        }
        simplify();
    }

    void simplify()
    {
        if (denominator < 0)
        {
            numerator *= -1;
            denominator *= -1;
        }

        int gcd = find_gcd(abs(numerator), denominator);
        numerator = numerator / gcd;
        denominator = denominator / gcd;
    }

    int getNumerator()
    {
        return numerator;
    }

    int getDenominator()
    {
        return denominator;
    }

    int compare(Fraction &f)
    {
        return sub(f).numerator;
    }
/*
    bool operator == (Fraction &f)
    {
        return compare(f) == 0;
    }

    bool operator < (Fraction &f)
    {
        return compare(f) < 0;
    }

    bool operator > (Fraction &f)
    {
        return compare(f) > 0;
    }
*/
    Fraction add(Fraction &f)
    {
        int num = (numerator * f.denominator) + (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction add(int n)
    {
        Fraction f(n);
        return add(f);
    }

    Fraction sub(Fraction &f)
    {
        // Can be implemented by Add
        int num = (numerator * f.denominator) - (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction sub(int n)
    {
        Fraction f(n);
        return sub(f);
    }

    Fraction mul(Fraction &f)
    {
        return Fraction(numerator * f.numerator, denominator * f.denominator);
    }

    Fraction mul(int n)
    {
        Fraction f(n);
        return mul(f);
    }

    Fraction div(Fraction &f)
    {
        if (f.numerator == 0)
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        else return Fraction(numerator * f.denominator, denominator * f.numerator);
    }

    Fraction div(int n)
    {
        Fraction f(n);
        return div(f);
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
    FractionCollection()
    {
        fractions = new Fraction[10];
        maxlength = 10;
        length = 0;
    }

    FractionCollection(int size)
    {
        fractions = new Fraction[size];
        maxlength = size;
        length = 0;
    }

    int size()
    {
        return length;
    }

    int getMaxlength()
    {
        return maxlength;
    }

    Fraction getFraction(int idx)
    {
        if (idx >= 0 || idx < length) return fractions[idx];

        else
        {
            cout << "Invalid index!" << endl;
            return Fraction();
        }
    }

    void insert(Fraction f)
    {
        if (length >= maxlength) cout << "No more space!" << endl;

        else
        {
            fractions[length] = f;
            length++;
        }
    }

    void insert(int pos, Fraction f)
    {
        if (pos >= maxlength || pos < 0) cout << "Invalid index!" << endl;

        else if (pos >= length)
        {
            fractions[pos] = f;
            length = pos + 1;
        }
        else
        {
            for (int i = length; i > pos; i--) fractions[i] = fractions[i-1];
            fractions[pos] = f;
            length++;
        }
    }

    void remove()
    {
        if (length > 0) length--;
        else cout << "Nothing to remove." << endl;
    }

    void remove(Fraction f)
    {
        int found = 0;
        for (int i = length-1; i >= 0; i--)
        {
            if (fractions[i].compare(f) == 0)
            {
                remove(i);
                found++;
            }
        }

        if (found == 0) cout << "No instances found" << endl;
    }

    void remove(int pos)
    {
        if (pos < 0 || pos >= length) cout << "Invalid index!" << endl;

        else
        {    
            for (int i = pos; i < length; i++) fractions[i] = fractions[i+1];
            length--;
        }
    }

    Fraction getmax()
    {
        if (length == 0) return Fraction();

        else
        {    
            int idx = 0;
            for (int i = 1; i < length; i++)
            {
                if (fractions[i].compare(fractions[idx]) > 0) idx = i;
            }
            return fractions[idx];
        }
    }

    Fraction getmin()
    {
        if (length == 0) return Fraction();

        else
        {    
            int idx = 0;
            for (int i = 1; i < length; i++)
            {
                if (fractions[i].compare(fractions[idx]) < 0) idx = i;
            }
            return fractions[idx];
        }
    }

    Fraction add(int start, int end)
    {
        if (start < 0 || start >= length || end < 0 || end >= length || start > end)
        {
            cout << "Invalid range!" << endl;
            return Fraction();
        }
        else
        {
            Fraction sum = fractions[start];
            for (int i = end; i > start; i--) sum = sum.add(fractions[i]);
            return sum;
        }
    }

    Fraction mul(int start, int end)
    {
        if (start < 0 || start >= length || end < 0 || end >= length || start > end)
        {
            cout << "Invalid range!" << endl;
            return Fraction();
        }
        else
        {
            Fraction product = fractions[start];
            for (int i = end; i > start; i--) product = product.mul(fractions[i]);
            return product;
        }
    }

    Fraction sub(int pos1, int pos2)
    {
        if (pos1 < 0 || pos1 >= length || pos2 < 0 || pos2 >= length)
        {
            cout << "Invalid index!" << endl;
            return Fraction();
        }
        else return fractions[pos1].sub(fractions[pos2]);
    }

    Fraction div(int pos1, int pos2)
    {
        if (pos1 < 0 || pos1 >= length || pos2 < 0 || pos2 >= length)
        {
            cout << "Invalid index!" << endl;
            return Fraction();
        }
        else return fractions[pos1].div(fractions[pos2]);
    }

    void print()
    {
        cout << endl << "Fractions" << endl;
        cout << "-------------------------------" << endl;

        for (int i = 0; i < length; i++)
        {
            cout << "Fraction " << i << ": ";
            fractions[i].print();
        }

        cout << "Max: ";
        getmax().print();
        cout << "Min: ";
        getmin().print();

        cout << "Summation: ";
        add(0, length-1).print();
        cout << "Multiplication: ";
        mul(0, length-1).print();
    }

    ~FractionCollection()
    {
        delete[] fractions;
    }
};


int main()
{
    // create Fraction with numerator, denominator
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
