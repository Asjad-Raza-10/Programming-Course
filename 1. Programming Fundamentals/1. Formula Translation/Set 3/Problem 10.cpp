#include <iostream>
#include <cmath>
using namespace std;

int main() {

    float x1 = -6, x2 = -12, x3 = 8, x4 = 13, x5 = 11, x6 = 6, x7 = 7, x8 = 2, x9 = -6, x10 = -9, x11 = -10, x12 = 11, x13 = 10, x14 = 9, x15 = 2, mean = 0, std_deviation = 0;
    

    mean = (x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8 + x9 + x10 + x11 + x12 + x13 + x14 + x15) / 15;

    std_deviation = sqrt(((pow(x1 - mean, 2) + pow(x2 - mean, 2) + pow(x3 - mean, 2) + pow(x4 - mean, 2) + pow(x5 - mean, 2) + pow(x6 - mean, 2) + pow(x7 - mean, 2) 
                    + pow(x8 - mean, 2) + pow(x9 - mean, 2) + pow(x10 - mean, 2) + pow(x11 - mean, 2) + pow(x12 - mean, 2) + pow(x13 - mean, 2) + pow(x14 - mean, 2) 
                    + pow(x15 - mean, 2)) / 15));


    cout << "Mean: " << mean << endl;
    cout << "Standard Deviation: " << std_deviation << endl;

    return 0;
}
