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

    Fraction(float f);

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

    Fraction operator+(const Fraction& f) const;

    Fraction operator+(const float f) const;

    Fraction operator-(const Fraction& f) const;

    Fraction operator-(const float f) const;

    Fraction operator*(const Fraction& f) const;

    Fraction operator*(const float f) const;

    Fraction operator/(const Fraction& f) const;

    Fraction operator/(const float f) const;

    Fraction operator+=(const Fraction& f);

    Fraction operator+=(const float f);

    Fraction operator-=(const Fraction& f);

    Fraction operator-=(const float f);

    Fraction operator*=(const Fraction& f);

    Fraction operator*=(const float f);

    Fraction operator/=(const Fraction& f);

    Fraction operator/=(const float f);

    // Friend Functions
    friend Fraction operator+(const float f1, const Fraction& f2);

    friend Fraction operator-(const float f1, const Fraction& f2);

    friend Fraction operator*(const float f1, const Fraction& f2);

    friend Fraction operator/(const float f1, const Fraction& f2);

    friend float operator+=(const float f1, const Fraction& f2);

    friend float operator-=(const float f1, const Fraction& f2);

    friend float operator*=(const float f1, const Fraction& f2);

    friend float operator/=(const float f1, const Fraction& f2);

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

    Fraction& operator[](int idx) const;

    FractionVector operator+(const FractionVector& fv) const;

    FractionVector operator-(const FractionVector& fv) const;

    Fraction operator*(const FractionVector& fv) const; // Dot Product

    FractionVector operator*(const Fraction& f) const;

    FractionVector operator/(const Fraction& f) const;

    Fraction value() const;

    // Friend Functions
    friend FractionVector operator*(const Fraction& f, const FractionVector& fv);

    friend ostream& operator<<(ostream& os, const FractionVector& fv);

    ~FractionVector();
};


class FractionMatrix
{
    int rowNum;
    int colNum;
    int rowCapacity;
    int colCapacity;
    FractionVector* row;
    FractionVector* column;

public:
    FractionMatrix();

    FractionMatrix(FractionVector* row, int rowNum);

    FractionMatrix(const FractionMatrix& fm);

    FractionVector getColumn(int idx) const;

    FractionVector& operator[](int idx) const;

    FractionMatrix operator+(const FractionMatrix& fm) const;

    FractionMatrix operator-(const FractionMatrix& fm) const;

    FractionMatrix operator*(const FractionMatrix& fm) const;

    FractionMatrix operator*(const Fraction& f) const;

    FractionMatrix operator/(const Fraction& f) const;

    FractionMatrix operator%(const FractionMatrix& fm) const;

    FractionMatrix transpose() const;

    // Friend Functions
    friend FractionMatrix operator*(const Fraction& f, const FractionMatrix& fm);

    friend ostream& operator<<(ostream& os, const FractionMatrix& fm);

    ~FractionMatrix();
};

