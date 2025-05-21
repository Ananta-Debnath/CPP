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

    Fraction(float f)
    {
        numerator = (int)(f*100);
        denominator = 100;

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

    float value() const
    {
        return (float)numerator / denominator;
    }

    Fraction operator+(const Fraction& f)
    {
        int num = (numerator * f.denominator) + (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction operator+(const float f)
    {
        Fraction fr(f);
        return (*this + fr);
    }

    Fraction operator-(const Fraction& f)
    {
        int num = (numerator * f.denominator) - (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const float f)
    {
        Fraction fr(f);
        return (*this - fr);
    }

    Fraction operator*(const Fraction& f)
    {
        return Fraction(numerator * f.numerator, denominator * f.denominator);
    }

    Fraction operator*(const float f)
    {
        Fraction fr(f);
        return (*this * fr);
    }

    Fraction operator/(const Fraction& f)
    {
        if (f.numerator == 0)
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        else return Fraction(numerator * f.denominator, denominator * f.numerator);
    }

    Fraction operator/(const float f)
    {
        Fraction fr(f);
        return (*this / fr);
    }

    Fraction operator+=(const Fraction& f)
    {
        *this = *this + f;
        return *this;
    }

    Fraction operator+=(const float f)
    {
        *this = *this + f;
        return *this;
    }

    Fraction operator-=(const Fraction& f)
    {
        *this = *this - f;
        return *this;
    }

    Fraction operator-=(const float f)
    {
        *this = *this - f;
        return *this;
    }

    Fraction operator*=(const Fraction& f)
    {
        *this = *this * f;
        return *this;
    }

    Fraction operator*=(const float f)
    {
        *this = *this * f;
        return *this;
    }

    Fraction operator/=(const Fraction& f)
    {
        *this = *this / f;
        return *this;
    }

    Fraction operator/=(const float f)
    {
        *this = *this / f;
        return *this;
    }

    // Friend Functions
    friend Fraction operator+(const float f1, const Fraction& f2);

    friend Fraction operator-(const float f1, const Fraction& f2);

    friend Fraction operator*(const float f1, const Fraction& f2);

    friend Fraction operator/(const float f1, const Fraction& f2);

    friend float operator+=(float& f1, const Fraction& f2);
    
    friend float operator-=(float& f1, const Fraction& f2);

    friend float operator*=(float& f1, const Fraction& f2);

    friend float operator/=(float& f1, const Fraction& f2);

    friend ostream& operator<<(ostream& os, const Fraction& f);
};


class FractionVector
{
    Fraction* fractions;
    int capacity;
    int fractionCount;

public:
    FractionVector();

    FractionVector(int capacity);

    FractionVector(const FractionVector& fv);

    Fraction& operator[](int idx);

    FractionVector operator+(const FractionVector& fv);

    FractionVector operator-(const FractionVector& fv);

    FractionVector operator*(const FractionVector& fv); // Dot Product

    FractionVector operator*(const Fraction& f);

    FractionVector operator/(const FractionVector& fv);

    Fraction value();

    // Friend Functions
    friend FractionVector operator*(const Fraction& f, const FractionVector& fv);

    friend ostream& operator<<(ostream& os, const FractionVector& fv);

    ~FractionVector();
};


class FractionMatrix
{
    int rowNum;
    int colNum;
    FractionVector* row;
    FractionVector* column;

public:
    FractionMatrix();

    FractionMatrix(FractionVector* row, int rowNum);

    FractionMatrix(const FractionMatrix& fm);

    FractionVector getColumn(int idx);

    FractionVector& operator[](int idx);

    FractionMatrix operator+(const FractionMatrix& fm);

    FractionMatrix operator-(const FractionMatrix& fm);

    FractionMatrix operator*(const FractionMatrix& fm);

    FractionMatrix operator*(const Fraction& f);

    FractionMatrix operator/(const Fraction& f);

    FractionMatrix operator%(const FractionMatrix& fm);

    FractionMatrix transpose();

    // Friend Functions
    friend FractionMatrix operator*(const Fraction& f, const FractionMatrix& fm);

    friend ostream& operator<<(ostream& os, const FractionMatrix& fm);

    ~FractionMatrix();
};


// Implement Friend Functions

// Fraction
Fraction operator+(const float f1, const Fraction& f2)
{
    Fraction f(f1);
    return (f + f2);
}

Fraction operator-(const float f1, const Fraction& f2)
{
    Fraction f(f1);
    return (f - f2);
}

Fraction operator*(const float f1, const Fraction& f2)
{
    Fraction f(f1);
    return (f * f2);
}

Fraction operator/(const float f1, const Fraction& f2)
{
    Fraction f(f1);
    return (f / f2);
}

float operator+=(float& f1, const Fraction& f2)
{
    f1 += f2.value();
    return f1;
}

float operator-=(float& f1, const Fraction& f2)
{
    f1 -= f2.value();
    return f1;
}

float operator*=(float& f1, const Fraction& f2)
{
    f1 *= f2.value();
    return f1;
}

float operator/=(float& f1, const Fraction& f2)
{
    f1 /= f2.value();
    return f1;
}

ostream& operator<<(ostream& os, const Fraction& f)
{
    os << f.numerator << "/" << f.denominator;
    return os;
}



int main()
{
    // Fraction Test Cases
    cout << "Fraction Tests" << endl;
    cout << "==================================" << endl;

    Fraction f1(6, 17);
    Fraction f2(8, 24);
    float f3 = 2.84;

    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "Fraction of f3 = " << Fraction(f3) << endl;
    cout << "Value of f1 = " << f1.value() << endl;
    cout << endl;

    cout << "Fraction + Fraction:" << endl;
    cout << "f1 + f2 = " << (f1 + f2) << endl;
    cout << "f1 - f2 = " << (f1 - f2) << endl;
    cout << "f1 * f2 = " << (f1 * f2) << endl;
    cout << "f1 / f2 = " << (f1 / f2) << endl;
    cout << endl;

    cout << "Fraction + Float:" << endl;
    cout << "f1 + f3 = " << (f1 + f3) << endl;
    cout << "f1 - f3 = " << (f1 - f3) << endl;
    cout << "f1 * f3 = " << (f1 * f3) << endl;
    cout << "f1 / f3 = " << (f1 / f3) << endl;
    cout << endl;

    cout << "Float + Fraction:" << endl;
    cout << "f3 + f2 = " << (f3 + f2) << endl;
    cout << "f3 - f2 = " << (f3 - f2) << endl;
    cout << "f3 * f2 = " << (f3 * f2) << endl;
    cout << "f3 / f2 = " << (f3 / f2) << endl;
    cout << endl;

    cout << "Fraction += Fraction:" << endl;
    f1 += f2;
    cout << "f1 += f2 -> " << f1 << endl;
    f1 -= f2;
    cout << "f1 -= f2 -> " << f1 << endl;
    f1 *= f2;
    cout << "f1 *= f2 -> " << f1 << endl;
    f1 /= f2;
    cout << "f1 /= f2 -> " << f1 << endl;
    cout << endl;

    cout << "Fraction += Float:" << endl;
    f1 += f3;
    cout << "f1 += f3 -> " << f1 << endl;
    f1 -= f3;
    cout << "f1 -= f3 -> " << f1 << endl;
    f1 *= f3;
    cout << "f1 *= f3 -> " << f1 << endl;
    f1 /= f3;
    cout << "f1 /= f3 -> " << f1 << endl;
    cout << endl;

    cout << "Float += Fraction:" << endl;
    f3 += f2;
    cout << "f3 += f2 -> " << f3 << endl;
    f3 -= f2;
    cout << "f3 -= f2 -> " << f3 << endl;
    f3 *= f2;
    cout << "f3 *= f2 -> " << f3 << endl;
    f3 /= f2;
    cout << "f3 /= f2 -> " << f3 << endl;
    cout << endl;
    
    cout << "==================================" << endl;
}