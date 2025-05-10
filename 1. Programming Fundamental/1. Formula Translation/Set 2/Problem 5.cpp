#include <iostream>

using namespace std;
int main()
{

    int a = 0, b = 0, ans = 0, rem = 0;

    cout << "Enter the first number" << endl;
    cin >> a;

    cout << "Enter the second number" << endl;
    cin >> b;

    ans = a / 3;
    rem = a % b;

    cout << a << "/" << b << ", answer = " << ans << ", remander = " << rem << endl;

    system("pause");

    return 0;
}