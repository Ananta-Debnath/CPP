#include<bits/stdc++.h>
using namespace std;

class Fraction{
    private:
        int numerator;
        int denominator;
    
        int gcd(int a, int b){
            int temp;

            while(b>0){
                temp=a%b;
                a=b;
                b=temp;
            }

            return a;
        }


        void reduce(){
            int common=gcd(abs(numerator),abs(denominator));

            numerator/=common;
            denominator/=common;

            if(denominator<0){
                numerator=-numerator;
                denominator=-denominator;
            }
        }
    
    
    public:
    //constructor

        Fraction(){
            numerator=0;
            denominator=1;
        }

        Fraction(int n){
            numerator=n;
            denominator=1;
        }

        Fraction(int a, int b){
            numerator=a;
            denominator=b;

            // if(b==0){

            // }

            reduce();
        }

    //destructor 
        ~Fraction(){}

    Fraction add(Fraction &f){
        int a= numerator*f.denominator+ f.numerator*denominator;
        int b= denominator*f.denominator;

        return Fraction(a,b);
    }

    Fraction add(int n){
        Fraction obj(n);

        return add(obj);
    }

    Fraction sub(Fraction &f){

        int a= numerator*f.denominator- f.numerator*denominator;
        int b= denominator*f.denominator;

        return Fraction(a,b);
    }

    Fraction sub(int n){

        Fraction obj(n);

        return sub(obj);
    }

    Fraction mul(Fraction &f){
        int a= numerator*f.numerator;
        int b= denominator*f.denominator;

        return Fraction(a,b);
    }

    Fraction mul(int n){
        Fraction obj(n);

        return mul(obj);
    }

    Fraction div(Fraction &f){
        if(f.numerator==0){
            cout<<" Can not divide by 0 "<<endl;
            return *this;
        }
        int a= numerator*f.denominator;
        int b= denominator*f.numerator;

        return Fraction(a,b);
    }

    Fraction div(int n){
        if(n==0){
            cout<< " Can not be divided by 0 "<<endl;
            return *this;
        }

        Fraction obj(n);

        return div(obj);
    }


    void print(){

        if(denominator==1){
            cout<<numerator<<endl;
        }else{
            cout<<numerator<<"/"<<denominator<<endl;
        }
    }

    int getNumerator(){

        return numerator; 

    }
    int getDenominator(){ 

        return denominator; 
    }

    bool operator>(const Fraction& f){
        return numerator*f.denominator > f.numerator*denominator;
    }

    bool operator<(const Fraction& f){
        return numerator*f.denominator < f.numerator*denominator;
    }

    bool operator==(const Fraction& f){
        return (numerator==f.numerator && denominator==f.denominator);
    }

};







class FractionCollection
{
    Fraction *fractions;
    int maxlength;
    int length;

public:
    FractionCollection(){
        maxlength=10;
        length=0;

        fractions=new Fraction[maxlength];
    }

    FractionCollection(int size){
        maxlength=size;
        length=0;

        fractions= new Fraction[maxlength];
    }

    void insert(Fraction f){
        if(length==maxlength){
            cout<<"Not enough space"<<endl;
            return;
        }

        fractions[length++]=f;
    }

    void insert(int pos, Fraction f){

        if(length==maxlength){
            cout<<"Not enough space"<<endl;
            return;
        }
        if(pos<0 || pos> length){
            cout<<"Invalid position.Try again."<<endl;
            return;
        }

        for(int i= length;i>pos;i--){
            fractions[i]=fractions[i-1];
        }
        fractions[pos]=f;
        length++;


    }

    void remove(){
        length--;
    }

    void remove(Fraction f){
        for (int i = 0; i < length; i++) {
            if (fractions[i] == f) {
                for (int j = i; j < length-1; j++) {
                    fractions[j] = fractions[j+1];
                }
                length--;
                break;
            }
        }
    }

    void remove(int pos){
        if(pos<0 || pos>length){
            cout<<"Invalid position.Try again."<<endl;
            return;
        }

        for(int i=pos;i<length;i++){
            fractions[i]=fractions[i+1];
        }
        length--;


    }

    Fraction getmax(){
        Fraction maximum=fractions[0];
        for(int i=0;i<length;i++){
            if(fractions[i]>maximum){
                maximum=fractions[i];
            }
        }

        return maximum;
    }

    Fraction getmin(){
        Fraction minimum=fractions[0];
        for(int i=0;i<length;i++){
            if(fractions[i]<minimum){
                minimum=fractions[i];
            }
        }

        return minimum;
    }

    Fraction add(int start, int end){

        if(start<0||end>length||start>end){
            return Fraction();
        }

        Fraction sum;

        for(int i=start;i<=end;i++){
            sum= sum.add(fractions[i]);
        }

        return sum;
    }

    Fraction mul(int start, int end){

        if(start<0||end>length||start>end){
            return Fraction();
        }

        Fraction ans(1);

        for(int i=start;i<=end;i++){

            ans=ans.mul(fractions[i]);
        }

        return ans;

    }

    Fraction sub(int pos1, int pos2){
        
        if(pos1<0 || pos1>= length || pos2<0 || pos2>=length){
            return Fraction();
        }

        return fractions[pos1].sub(fractions[pos2]);
    }

    Fraction div(int pos1, int pos2){
        if(pos1<0 || pos1>= length || pos2<0 || pos2>=length){
            return Fraction();
        }

        return fractions[pos1].div(fractions[pos2]);

    }

    void print(){

        cout<<"fractions"<<endl;
        cout<<"--------------"<<endl;

        for(int i=0;i<length;i++){
            cout<<"Fraction "<<i<<": ";
            fractions[i].print();
        }

        cout<<"Max: ";
        getmax().print();

        cout<<"Min: ";
        getmin().print();

        cout<<"Summation: ";
        add(0,length-1).print();

        cout<<"Multiplication: ";
        mul(0,length-1).print();
    }

    ~FractionCollection(){
        delete[] fractions;
    }
};







int main()
{
    // Test 1: Fraction creation and simplification
    cout << "Test 1: Fraction Creation and Simplification" << endl;
    Fraction f1(4, 8); // Should simplify to 1/2
    Fraction f2(-6, -9); // Should simplify to 2/3
    Fraction f3(0, 5); // Should remain 0/1
    Fraction f4(5, 5); // Should handle denominator = 0
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
/*
    cout << (f5.compare(f6) == 0) << endl; // Should print 0 (false)
    cout << (f5.compare(f6) < 0) << endl;  // Should print 0 (false)
    cout << (f5.compare(f6) > 0) << endl;  // Should print 1 (true)
*/
    cout << (f5 == f6) << endl; // Should print 0 (false)
    cout << (f5 < f6) << endl;  // Should print 0 (false)
    cout << (f5 > f6) << endl;  // Should print 1 (true)

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