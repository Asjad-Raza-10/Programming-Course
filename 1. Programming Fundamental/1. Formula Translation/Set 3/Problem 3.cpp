#include <iostream>
using namespace std;

int main() 
{
    float rate = 0.0, svcCharge = 0.0, telCharge = 0.0, roomCharge = 0.0, total = 0.0;
    int nights = 0;

    cout << "Enter the per-night rate for the room: $";
    cin >> rate;

    cout << "Enter the number of nights stayed: ";
    cin >> nights;

    cout << "Enter the room service charge (enter 0 if no charge): $";
    cin >> svcCharge;

    cout << "Enter the telephone charge (enter 0 if no charge): $";
    cin >> telCharge;

    roomCharge = rate * nights;
    total = roomCharge + svcCharge + telCharge;

    cout << "Room charge for " << nights << " nights: $" << roomCharge << endl;
    cout << "Room service charge: $" << svcCharge << endl;
    cout << "Telephone charge: $" << telCharge << endl;
    cout << "Total bill: $" << total << endl;

    return 0;
}
