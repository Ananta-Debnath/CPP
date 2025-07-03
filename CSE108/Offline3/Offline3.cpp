#include <iostream>
#include <iomanip> 
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
            throw runtime_error ("Denominator cannot be zero!");
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
        numerator = (int)(f * 100);
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
        *this = (*this) + f;
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
        fractionCount = fv.fractionCount;
        fractions = new Fraction[capacity];

        for (int i = 0; i < fv.fractionCount; i++) fractions[i] = fv.fractions[i];
    }

    void setCapacity(int capacity)
    {
        if (capacity > 0)
        {
            if (fractionCount > capacity) fractionCount = capacity;

            this->capacity = capacity;
            Fraction* newFractions = new Fraction[capacity];

            for (int i = 0; i < fractionCount; i++) newFractions[i] = fractions[i];

            delete[] fractions;
            fractions = newFractions;
        }
    }

    FractionVector& operator=(const FractionVector& fv)
    {
        if (this != &fv)
        {
            if (fractions != NULL) delete[] fractions;

            capacity = fv.capacity;
            fractionCount = 0;
            fractions = new Fraction[capacity];

            for (int i = 0; i < fv.fractionCount; i++) addFraction(fv.fractions[i]);
        }

        return *this;
    }

    int size() const
    {
        return fractionCount;
    }

    void addFraction(const Fraction& f)
    {
        if (fractionCount < capacity) fractions[fractionCount++] = f;

        else cout << "No more space for adding fraction!" << endl;
    }

    void removeFraction(int idx)
    {
        if (idx >= 0 && idx < fractionCount)
        {
            fractionCount--;
            for (int i = idx; i < fractionCount; i++)
            {
                fractions[i] = fractions[i+1];
            }
        }

        else if (fractionCount == 0) cout << "No fraction in list!" << endl;

        else cout << "Invalid Index!" << endl;
    }

    Fraction& operator[](int idx) const
    {
        if (idx < fractionCount && idx >= 0) return fractions[idx];

        else throw runtime_error("Index out of range!");
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
        for (int i = 0; i < fractionCount; i++)
            val += (fractions[i] * fractions[i]);

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
    int rowCapacity;
    int colCapacity;
    FractionVector* row;
    FractionVector* col;

public:
    FractionMatrix(int rowCapacity = 1, int colCapacity = 1, int rowNum = 0, FractionVector* row = NULL)
    {
        this->rowCapacity = rowCapacity;
        this->colCapacity = colCapacity;
        this->rowNum = 0;
        colNum = 0;
        this->row = new FractionVector[rowCapacity];
        col = new FractionVector[colCapacity];

        for (int i = 0; i < rowCapacity; i++) this->row[i] = FractionVector(colCapacity);
        for (int i = 0; i < colCapacity; i++) col[i] = FractionVector(rowCapacity);

        if (row != NULL && row[0].size() <= colCapacity)
        {
            for (int i = 0; i < rowNum; i++) addRow(row[i]);
        }
    }

    FractionMatrix(const FractionMatrix& fm)
    {
        rowCapacity = fm.rowCapacity;
        colCapacity = fm.colCapacity;
        rowNum = fm.rowNum;
        colNum = fm.colNum;
        row = new FractionVector[rowCapacity];
        col = new FractionVector[colCapacity];

        for (int i = 0; i < rowCapacity; i++) row[i] = fm.row[i];
        for (int i = 0; i < colCapacity; i++) col[i] = fm.col[i];
    }

    FractionMatrix operator=(const FractionMatrix& fm)
    {
        if (this != &fm)
        {
            if (row != NULL) delete[] row;
            if (col != NULL) delete[] col;

            rowCapacity = fm.rowCapacity;
            colCapacity = fm.colCapacity;
            rowNum = fm.rowNum;
            colNum = fm.colNum;
            row = new FractionVector[rowCapacity];
            col = new FractionVector[colCapacity];

            for (int i = 0; i < rowCapacity; i++) row[i] = fm.row[i];
            for (int i = 0; i < colCapacity; i++) col[i] = fm.col[i];
        }

        return *this;
    }

    void setColumn()
    {
        for (int i = 0; i < colNum; i++)
        {
            for (int j = 0; j < rowNum; j++)
            {
                col[i][j] = row[j][i];
            }
        }
    }

    void addRow(const FractionVector& fv)
    {
        if (colNum == 0) colNum = fv.size();
        
        if (rowNum < rowCapacity && fv.size() == colNum)
        {
            row[rowNum] = fv;
            row[rowNum].setCapacity(colCapacity);
            rowNum++;

            for (int i = 0; i < colNum; i++) col[i].addFraction(fv[i]);
        }

        else if (rowNum >= rowCapacity) cout << "Cannot have more row!" << endl;

        else cout << "Invalid FractionVector!" << endl;
    }

    void addColumn(const FractionVector& fv)
    {
        if (rowNum == 0) rowNum = fv.size();
        
        if (colNum < colCapacity && fv.size() == rowNum)
        {
            col[colNum] = fv;
            col[colNum].setCapacity(colCapacity);
            colNum++;

            for (int i = 0; i < rowNum; i++) row[i].addFraction(fv[i]);
        }

        else if (colNum >= colCapacity) cout << "Cannot have more column!" << endl;

        else cout << "Invalid FractionVector!" << endl;
    }

    void removeRow(int idx)
    {
        if (idx >= 0 && idx < rowNum)
        {
            rowNum--;
            for (int i = idx; i < rowNum; i++)
            {
                row[i] = row[i+1];
            }
            for (int i = 0; i < colNum; i++)
            {
                col[i].removeFraction(idx);
            }
        }

        else if (rowNum == 0) cout << "No row in matrix!" << endl;

        else cout << "Invalid Index!" << endl;
    }

    void removeColumn(int idx)
    {
        if (idx >= 0 && idx < colNum)
        {
            colNum--;
            for (int i = idx; i < colNum; i++)
            {
                col[i] = col[i+1];
            }
            for (int i = 0; i < rowNum; i++)
            {
                row[i].removeFraction(idx);
            }
        }

        else if (colNum == 0) cout << "No column in matrix!" << endl;

        else cout << "Invalid Index!" << endl;
    }

    FractionVector getColumn(int idx)
    {
        setColumn();

        if (idx < colNum) return col[idx];

        else throw runtime_error("Index out of range!");
    }

    FractionVector& operator[](int idx) const
    {
        if (idx < rowNum) return row[idx];

        else throw runtime_error("Index out of range!");
    }

    FractionMatrix operator+(const FractionMatrix& fm) const
    {
        if (rowNum == fm.rowNum && colNum == fm.colNum)
        {
            FractionMatrix newMatrix(rowNum, colNum);
            for (int i = 0; i < rowNum; i++) newMatrix.addRow(row[i] + fm.row[i]);
            return newMatrix;
        }

        else
        {
            cout << "These matrices are of different sizes" << endl;
            return *this;
        }
    }

    FractionMatrix operator-(const FractionMatrix& fm) const
    {
        if (rowNum == fm.rowNum && colNum == fm.colNum)
        {
            FractionMatrix newMatrix(rowNum, colNum);
            for (int i = 0; i < rowNum; i++) newMatrix.addRow(row[i] - fm.row[i]);
            return newMatrix;
        }

        else
        {
            cout << "These matrices are of different sizes" << endl;
            return *this;
        }
    }

    FractionMatrix operator*(FractionMatrix& fm) const // Matrix Multiplication
    {
        if (colNum == fm.rowNum)
        {
            FractionMatrix newMatrix(rowNum, fm.colNum);
            FractionVector newRow = fm[0];

            for (int i = 0; i < rowNum; i++)
            {
                for (int j = 0; j < fm.colNum; j++) newRow[j] = row[i] * fm.getColumn(j);

                newMatrix.addRow(newRow);
            }

            return newMatrix;
        }
        else
        {
            cout << "These matrices are of different sizes" << endl;
            return *this;
        }
    }

    FractionMatrix operator*(const Fraction& f) const
    {
        FractionMatrix newMatrix = *this;
        for (int i = 0; i < rowNum; i++) newMatrix[i] = newMatrix[i] * f;

        return newMatrix;
    }

    FractionMatrix operator/(const Fraction& f) const
    {
        FractionMatrix newMatrix = *this;
        for (int i = 0; i < rowNum; i++) newMatrix[i] = newMatrix[i] / f;

        return newMatrix;
    }

    FractionMatrix operator%(const FractionMatrix& fm) const
    {
        if (rowNum == fm.rowNum && colNum == fm.colNum)
        {
            FractionMatrix newMatrix = *this;

            for (int i = 0; i < rowNum; i++)
            {
                for (int j = 0; j < fm.colNum; j++) newMatrix[i][j] *= fm[i][j];
            }
            newMatrix.setColumn();

            return newMatrix;
        }
        else
        {
            cout << "These matrices are of different sizes" << endl;
            return *this;
        }
    }

    FractionMatrix transpose()
    {
        setColumn();
        return FractionMatrix(colCapacity, rowCapacity, colNum, col);
    }

    // Friend Functions
    friend FractionMatrix operator*(const Fraction& f, const FractionMatrix& fm);

    friend ostream& operator<<(ostream& os, const FractionMatrix& fm);

    ~FractionMatrix()
    {
        delete[] row;
        delete[] col;
        // cout << "FractionMatrix Deleted!" << endl;
    }
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
    string str = to_string(f.numerator);
    if (f.denominator != 1)
    {
        str += '/';
        str += to_string(f.denominator);
    }
    os << str;
    return os;
}
/*
ostream& operator<<(ostream& os, const Fraction& f)
{
    os << f.numerator;
    if (f.denominator != 1) os << "/" << f.denominator;
    return os;
}
*/

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


// FractionMatrix
FractionMatrix operator*(const Fraction& f, const FractionMatrix& fm)
{
    return (fm * f);
}

ostream& operator<<(ostream& os, const FractionMatrix& fm)
{
    os << endl;
    for (int i = 0; i < fm.rowNum; i++)
    {
        os << "[";
        for (int j = 0; j < fm.colNum; j++)
        {
            os << setw(11) << fm[i][j] << "  ";
        }
        os << "]" << endl;
    }
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

    FractionVector fv1(3), fv2(3), fv3(2), fv4(2);
    fv1.addFraction(f1+f2);
    fv1.addFraction(f1-f2);
    fv1.addFraction(f1);
    fv2.addFraction(f2);
    fv2.addFraction(f1*f2);
    fv2.addFraction(f2-f1);
    fv3.addFraction(f3);
    fv3.addFraction(f3*f2);
    fv4.addFraction(f1);
    fv4.addFraction(f1*f2);

    fv1.addFraction(f1);
    cout << endl;

    cout << "fv1 = " << fv1 << endl;
    cout << "fv2 = " << fv2 << endl;
    cout << "fv3 = " << fv3 << endl;
    cout << "fv4 = " << fv4 << endl;
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
    cout << endl;

    cout << "==================================" << endl << endl;


    // FractionMatrix Test Cases
    cout << "FractionMatrix Tests" << endl;
    cout << "==================================" << endl;

    FractionMatrix fm1(3, 3), fm2(3, 3), fm3(3, 2);
    fm1.addRow(fv1);
    fm1.addRow(fv1 + fv2);
    fm1.addRow(fv1 - fv2);
    fm2.addRow(fv2 - fv1);
    fm2.addRow(fv2);
    fm2.addRow(fv2 * f1);
    fm3.addRow(fv4);
    fm3.addRow(fv3);
    fm3.addRow(fv4);

    fm1.addRow(fv2);
    cout << endl;

    cout << "fm1:" << fm1 << endl;
    cout << "fm2:" << fm2 << endl;
    cout << "fm3:" << fm3 << endl;
    cout << endl;

    cout << "Access Element:" << endl;
    cout << "fm1[1] = " << fm1[1] << endl;
    cout << "fm2[0][2] = " << fm2[0][2] << endl;
    cout << "fm3(col1) = " << fm3.getColumn(1) << endl;
    cout << endl;

    cout << "fm1 + fm2 = " << (fm1 + fm2) << endl;
    cout << "fm1 - fm2 = " << (fm1 - fm2) << endl;
    cout << endl;

    cout << "fm1 * f1 = " << (fm1 * f1) << endl;
    cout << "f1 * fm1 = " << (f1 * fm1) << endl;
    cout << "fm1 / f1 = " << (fm1 / f1) << endl;
    cout << endl;

    cout << "Matrix Multiplication:" << endl;
    cout << "fm2 * fm3 = " << fm2 * fm3 << endl;
    cout << endl;

    cout << "Hadamard Multiplication:" << endl;
    cout << "fm1 % fm2 = " << fm1 % fm2 << endl;
    cout << endl;

    cout << "Transpose of fm3:" << fm3.transpose() << endl;
    cout << endl;

    cout << "Invalid Operation:" << endl;
    fm1 + fm3;
    fm2 - fm3;
    fm3 * fm1;
    fm3 % fm2;
    try
    {
        fm1[4];
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }
    try
    {
        fm1.getColumn(4);
    }
    catch(const exception& e)
    {
        cerr << e.what() << endl;
    }
    cout << endl;

    cout << "==================================" << endl;


    return 0;
}
