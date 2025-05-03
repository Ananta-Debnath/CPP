#include<iostream>
using namespace std;
class ananta{
    
    int a;
    int b;
    public:
    ananta(){}
    ananta(int new_a, int new_b)
    {
        a = new_a;
        b = new_b;
    }
    void setA(int x)
    {
        a = x;
    }
    void operator++(int none)
    {
        a++;
        b++;
    
    }

   
    void show()
    {
        cout<<a<<" "<<b<<endl;
    }
};



int main()
{
    ananta wasik(8, 69);
    wasik++;
    wasik.show();

    ananta prithu;
    // ++wasik;
    prithu = wasik;
    
    prithu.show();


 


    

}