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
    Fraction(int num = 0, int denom = 1)
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

    Fraction squareRoot() const
    {
        if (this->value() >= 0) return Fraction(sqrt(this->value()));

        else
        {
            cout << "Cannot calculate square root of negative Fractions!" << endl;
            exit(-1);
        }
    }

    Fraction operator+(const Fraction& f) const
    {
        int num = (numerator * f.denominator) + (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction operator+(const float f) const
    {
        Fraction fr(f);
        return (*this + fr);
    }

    Fraction operator-(const Fraction& f) const
    {
        int num = (numerator * f.denominator) - (f.numerator * denominator);
        int denom = denominator * f.denominator;
        return Fraction(num, denom);
    }

    Fraction operator-(const float f) const
    {
        Fraction fr(f);
        return (*this - fr);
    }

    Fraction operator*(const Fraction& f) const
    {
        return Fraction(numerator * f.numerator, denominator * f.denominator);
    }

    Fraction operator*(const float f) const
    {
        Fraction fr(f);
        return (*this * fr);
    }

    Fraction operator/(const Fraction& f) const
    {
        if (f.numerator == 0)
        {
            cout << "Can not divide by 0" << endl;
            return *this;
        }
        else return Fraction(numerator * f.denominator, denominator * f.numerator);
    }

    Fraction operator/(const float f) const
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
    FractionVector(int capacity = 1, int fractionCount = 0, Fraction* fractions = NULL)
    {
        this->capacity = capacity;
        this->fractions = new Fraction[capacity];
        this->fractionCount = 0;

        if (fractions != NULL)
        {
            for (int i = 0; i < fractionCount; i++) this->addFraction(fractions[i]);
        }
    }

    FractionVector(const FractionVector& fv)
    {
        capacity = fv.capacity;
        fractionCount = 0;
        fractions = new Fraction[capacity];

        for (int i = 0; i < fv.fractionCount; i++) addFraction(fv.fractions[i]);
    }

    FractionVector& operator=(const FractionVector& fv)
    {
        if (fractions != NULL) delete[] fractions;

        capacity = fv.capacity;
        fractionCount = 0;
        fractions = new Fraction[capacity];

        for (int i = 0; i < fv.fractionCount; i++) addFraction(fv.fractions[i]);

        return *this;
    }

    void addFraction(const Fraction& f)
    {
        if (fractionCount < capacity) fractions[fractionCount++] = f;

        else cout << "No more space for adding fraction!" << endl;
    }

    Fraction& operator[](int idx) const
    {
        if (idx < fractionCount && idx >= 0) return fractions[idx];

        else
        {
            throw runtime_error("Index out of range!");
        }
    }

    FractionVector operator+(const FractionVector& fv) const
    {
        FractionVector newVector = *this;
        if (fractionCount == fv.fractionCount)
        {
            for (int i = 0; i < fractionCount; i++) newVector[i] += fv[i];
        }
        else cout << *this << " and " << fv << " have different size" << endl;

        return newVector;
    }

    FractionVector operator-(const FractionVector& fv) const
    {
        FractionVector newVector = *this;
        if (fractionCount == fv.fractionCount)
        {
            for (int i = 0; i < fractionCount; i++) newVector[i] -= fv[i];
        }
        else cout << *this << " and " << fv << " have different size" << endl;

        return newVector;
    }

    Fraction operator*(const FractionVector& fv) const // Dot Product
    {
        Fraction dot;

        if (fractionCount == fv.fractionCount)
        {
            for (int i = 0; i < fractionCount; i++) dot += (fractions[i] * fv[i]);
        }
        else cout << *this << " and " << fv << " have different size" << endl;

        return dot;
    }

    FractionVector operator*(const Fraction& f) const
    {
        FractionVector newVector = *this;
        for (int i = 0; i < fractionCount; i++) newVector[i] *= f;

        return newVector;
    }

    FractionVector operator/(const Fraction& f) const
    {
        FractionVector newVector = *this;
        for (int i = 0; i < fractionCount; i++) newVector[i] /= f;

        return newVector;
    }

    Fraction value() const
    {
        Fraction val;
        for (int i = 0; i < fractionCount; i++) val += (fractions[i] * fractions[i]);

        val = val.squareRoot();
        return val;
    }

    ~FractionVector()
    {
        if (fractions != NULL) delete[] fractions;
        // cout << "FractionVector Deleted!" << endl;
    }

    // Friend Functions
    friend FractionVector operator*(const Fraction& f, const FractionVector& fv);

    friend ostream& operator<<(ostream& os, const FractionVector& fv);
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
    os << f.numerator;
    if (f.denominator != 1) os << "/" << f.denominator;
    return os;
}

// FractionVector
FractionVector operator*(const Fraction& f, const FractionVector& fv)
{
    return (fv * f);
}

ostream& operator<<(ostream& os, const FractionVector& fv)
{
    os << "[";

    if (fv.fractionCount == 0) os << ".";

    else
    {
        os << fv[0];
        for (int i = 1; i < fv.fractionCount; i++) os << ", " << fv[i];
    }

    os << "]";
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

    cout << "==================================" << endl << endl;


    // FractionVector Test Cases
    cout << "FractionVector Tests" << endl;
    cout << "==================================" << endl;

    FractionVector fv1(3), fv2(3), fv3(2);
    fv1.addFraction(f1+f2);
    fv1.addFraction(f1-f2);
    fv1.addFraction(f1);
    fv2.addFraction(f2);
    fv2.addFraction(f1*f2);
    fv2.addFraction(f2-f1);
    fv3.addFraction(f3);
    fv3.addFraction(f3*f2);

    fv1.addFraction(f1);
    cout << endl;

    cout << "fv1 = " << fv1 << endl;
    cout << "fv2 = " << fv2 << endl;
    cout << "fv3 = " << fv3 << endl;
    cout << endl;

    cout << "Value of fv1 = " << fv1.value() << endl;
    cout << endl;

    cout << "Access Element:" << endl;
    cout << "fv1[1] = " << fv1[1] << endl;
    cout << endl;

    // cout << "FractionVector + FractionVector:" << endl;
    cout << "fv1 + fv2 = " << (fv1 + fv2) << endl;
    cout << "fv1 - fv2 = " << (fv1 - fv2) << endl;
    cout << endl;

    // cout << "FractionVector * Fraction:" << endl;
    cout << "fv1 * f1 = " << (fv1 * f1) << endl;
    cout << "f1 * fv2 = " << (f1 * fv2) << endl;
    cout << "fv1 / f1 = " << (fv1 / f1) << endl;
    cout << endl;

    cout << "Dot Product:" << endl;
    cout << "fv1 * fv2 = " << (fv1 * fv2) << endl;
    cout << endl;

    cout << "Invalid Operation:" << endl;
    fv1 + fv3;
    fv3 - fv2;
    fv1 * fv3;
    try
    {
        fv1[4];
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }

    cout << "==================================" << endl << endl;
}