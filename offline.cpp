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
        cout<<numerator<<"/"<<denominator<<endl;
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

        cout << endl << "Fractions" << endl;
        cout << "-------------------------------" << endl;

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

