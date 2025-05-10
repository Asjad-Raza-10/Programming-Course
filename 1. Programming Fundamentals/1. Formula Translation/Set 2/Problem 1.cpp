
#include <iostream>

using namespace std;
int main()
{
    int a = 0, b = 0, c = 0, d = 0, mul = 0, sub = 0, add = 0, ans1 = 0, ans2 = 0, ans3 = 0;
    float ans4 = 0.0;

    cout << "Enter a value for b"<<endl;
    cin >> b;

    a = b; //value of b is assigned to a

    cout << "a = b: \t a = " << b << endl;

    cout << "Enter a value for d"<<endl;
    cin >> d;

    a = d; //value of d is assigned to a
    c = a; //value of a is assigned to c

    cout << "c = a = d: \t a = ," << d <<" c = " << d << endl;

    mul = a * b;
    sub = a - b;
    add = a + b;
    ans1 = mul - add;
    ans2 = add - sub;
    ans3 = a * a + b * b + c * c - (2 * a * c);
    ans4= (float(a) * a + b * b + c * c) / (2 * a * c);

    cout << "the product of a and b is " << mul << endl;
    cout << "the difference between a and b is " << sub << endl;
    cout << "the sum of a and b is " << add << endl;
    cout << "the answer 1 is " << ans1 << endl;
    cout << "the answer 2 is " << ans2 << endl;
    cout << "the answer 3 is " << ans3 << endl;
    cout << "the answer 4 is " << ans4 << endl;

    system("pause");

    return 0;
}
