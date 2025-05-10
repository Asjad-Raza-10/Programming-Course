#include <iostream>

using namespace std;
int main()
{

    float gsal, nets, prv, gst, grs_anl, net_anl;

    cout << "Enter your gross salary:";
    cin >> gsal;

    cout << endl;

    prv = 0.05 * gsal;
    gst = 0.16 * gsal;
    nets = gsal - prv - gst;

    cout << "Provident Fund: " << prv << "\nGovernment Sales Tax: " << gst << "\n\nNet Salary after above mentioned deductions: " << nets << endl << endl;

    grs_anl = gsal * 12;
    net_anl = nets * 12;
    
    cout << "Your gross annual salary is: " << grs_anl << endl << "Your net annual salary is: " << net_anl << endl;
    
    prv *= 12 * 2;
    cout << "Your provident fund at the end of the year will be: " << prv << endl << endl;

    gsal *= 1.015;
    cout << "Your gross salary each month for the next year afer 3% increment and 1.5% tax deduction will be: " << gsal << endl;
    gsal *= 1.015;
    cout << "Your gross salary each month for the 2nd next year afer 3% increment and 1.5% tax deduction will be: " << gsal << endl;

    cout << endl;
    system("pause");

    return 0;
}