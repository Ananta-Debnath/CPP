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
        return Fraction(numerator + (n * denominator), denominator);
    }

    Fraction sub(Fraction &f)
    {
        int num = (numerator * f.denominator) - (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction sub(int n)
    {
        return Fraction(numerator - (n * denominator), denominator);
    }

    Fraction mul(Fraction &f)
    {
        return Fraction(numerator * f.numerator, denominator * f.denominator);
    }

    Fraction mul(int n)
    {
        return Fraction(n * numerator, denominator);
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
        if (n == 0)
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        else return Fraction(numerator, n * denominator);
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
        if (pos >= maxlength || pos < 0) cout << "Invalid Index!" << endl;

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
        if (pos < 0 || pos >= length) cout << "Invalid Index!" << endl;

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
        if (start < 0 || end >= length)
        {
            cout << "Invalid Index!" << endl;
            return Fraction();
        }
        else
        {
            Fraction tmp = fractions[start];
            for (int i = end; i > start; i--) tmp = tmp.add(fractions[i]);
            return tmp;
        }
    }

    Fraction mul(int start, int end)
    {
        if (start < 0 || end >= length)
        {
            cout << "Invalid Index!" << endl;
            return Fraction();
        }
        else
        {
            Fraction tmp = fractions[start];
            for (int i = end; i > start; i--) tmp = tmp.mul(fractions[i]);
            return tmp;
        }
    }

    Fraction sub(int pos1, int pos2)
    {
        if (pos1 < 0 || pos1 >= length || pos2 < 0 || pos2 >= length)
        {
            cout << "Invalid Index!" << endl;
            return Fraction();
        }
        else return fractions[pos1].sub(fractions[pos2]);
    }

    Fraction div(int pos1, int pos2)
    {
        if (pos1 < 0 || pos1 >= length || pos2 < 0 || pos2 >= length)
        {
            cout << "Invalid Index!" << endl;
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

/*
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
*/


// Test Cases by GitHub Copilot
int main()
{
    // Test 1: Fraction creation and simplification
    cout << "Test 1: Fraction Creation and Simplification" << endl;
    Fraction f1(4, 8); // Should simplify to 1/2
    Fraction f2(-6, -9); // Should simplify to 2/3
    Fraction f3(0, 5); // Should remain 0/1
    Fraction f4(5, 0); // Should handle denominator = 0
    f1.print();
    f2.print();
    f3.print();
    f4.print();
    cout << endl;

    // Test 2: Arithmetic operations
    cout << "Test 2: Arithmetic Operations" << endl;
    Fraction f5(3, 4), f6(2, 5);
    (f5.add(f6)).print(); // Addition
    (f5.sub(f6)).print(); // Subtraction
    (f5.mul(f6)).print(); // Multiplication
    (f5.div(f6)).print(); // Division
    // (f5.div(Fraction(0, 1))).print(); // Division by zero
    cout << endl;

    // Test 3: Comparison operators
    cout << "Test 3: Comparison Operators" << endl;
    cout << (f5.compare(f6) == 0) << endl; // Should print 0 (false)
    cout << (f5.compare(f6) < 0) << endl;  // Should print 0 (false)
    cout << (f5.compare(f6) > 0) << endl;  // Should print 1 (true)
/*
    cout << (f5 == f6) << endl; // Should print 0 (false)
    cout << (f5 < f6) << endl;  // Should print 0 (false)
    cout << (f5 > f6) << endl;  // Should print 1 (true)
*/
    cout << endl;

    // Test 4: FractionCollection basic operations
    cout << "Test 4: FractionCollection Basic Operations" << endl;
    FractionCollection fc(5);
    fc.insert(f1);
    fc.insert(f2);
    fc.insert(f3);
    fc.insert(f4);
    fc.print();
    cout << endl;

    // Test 5: Insert at specific position
    cout << "Test 5: Insert at Specific Position" << endl;
    fc.insert(2, f5); // Insert at position 2
    fc.print();
    cout << endl;

    // Test 6: Remove by position and value
    cout << "Test 6: Remove by Position and Value" << endl;
    fc.remove(1); // Remove at position 1
    fc.print();
    fc.remove(f5); // Remove all instances of f5
    fc.print();
    cout << endl;

    // Test 7: Get max and min fractions
    cout << "Test 7: Get Max and Min Fractions" << endl;
    fc.getmax().print(); // Should print the largest fraction
    fc.getmin().print(); // Should print the smallest fraction
    cout << endl;

    // Test 8: Add and multiply fractions in a range
    cout << "Test 8: Add and Multiply Fractions in a Range" << endl;
    fc.add(0, 2).print(); // Add fractions from index 0 to 2
    fc.mul(0, 2).print(); // Multiply fractions from index 0 to 2
    cout << endl;

    // Test 9: Invalid operations
    cout << "Test 9: Invalid Operations" << endl;
    fc.insert(10, f6); // Invalid index
    fc.remove(10);     // Invalid index
    fc.add(-1, 5).print(); // Invalid range
    fc.mul(0, 10).print(); // Invalid range
    cout << endl;

    // Test 10: Dynamic resizing (if implemented)
    cout << "Test 10: Dynamic Resizing" << endl;
    FractionCollection fc2(2);
    fc2.insert(f1);
    fc2.insert(f2);
    fc2.insert(f3); // Should trigger resizing if implemented
    fc2.print();
    cout << endl;

    return 0;
}