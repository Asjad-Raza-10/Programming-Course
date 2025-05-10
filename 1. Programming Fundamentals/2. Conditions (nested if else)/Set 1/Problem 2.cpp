#include <iostream>
using namespace std;

int main()
{
    int low = 1, high = 100, mid = 0;
    char response = ' ';

    cout << "Think of a number between 1 and 100." << endl;
    cout << "Enter Y for yes and N for no" << endl;

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
        cout << endl;
        return 0;
    }

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
        cout << endl;
        return 0;
    }

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
        cout << endl;
        return 0;
    }

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
        cout << endl;
        return 0;
    }

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
        cout << endl;
        return 0;
    }

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
        cout << endl;
        return 0;
    }

    mid = (low + high) / 2;
    cout << "Is the number greater than " << mid << "? (y/n): ";
    cin >> response;

    if (response == 'Y' || response == 'y') {
        low = mid + 1;
    }
    else {
        high = mid;
    }

    if (low == high) {
        cout << "Your number is: " << low << endl;
    }

    cout << endl;

    return 0;
}
