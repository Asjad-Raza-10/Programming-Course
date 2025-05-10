#include <iostream>
#include <cmath>

using namespace std;

int main()
{   
    float a=0, b=0, c=0, d=0, x1=0, x2=0;

    cout<<"Enter the values of a, b, and c for quadratic equation."<<endl;
    
    cout<<"Value of a: ";
    cin>>a;

    cout<<"Value of b: ";
    cin>>b;

    cout<<"Value of c: ";
    cin>>c;

    d = (b*b) - (4*a*c);

    if (d > 0) 
    {
       
        x1 = (-b + sqrt(d)) / (2 * a);
        x2 = (-b - sqrt(d)) / (2 * a);
        cout << "The roots of the equation are: " << x1 << " and " << x2 << endl;
    } 
    else if (d == 0) {
        
        x1 = -b / (2 * a);
        x2 = x1;
        cout << "The roots of the equation are equal: " << x1 << " and " << x2 << endl;
    } 
    else {
        // Complex roots
        float realPart = -b / (2 * a);
        float imaginaryPart = sqrt(-d) / (2 * a);
        cout << "The roots of the equation are: " 
             << realPart << " + " << imaginaryPart << "i and " 
             << realPart << " - " << imaginaryPart << "i" << endl;
    }

    return 0;
}
