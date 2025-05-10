#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    float A=0, p=0, a=0, b=0, c=0;

    cout<<"Enter the lengths of 3 sides of the triangle:"<<endl;
    cin>>a>>b>>c;

    p=(a+b+c)/2;
    A=sqrt(p*(p-a)*(p-b)*(p-c));
    
    cout<<endl<<"Area of the triangle is: "<<A<<" units square.";

    cout<<endl;
    return 0;
}