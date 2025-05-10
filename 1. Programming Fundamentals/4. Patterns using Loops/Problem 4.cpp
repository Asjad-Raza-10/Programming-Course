#include <iostream>
using namespace std;

int main()
{

    int std_no = 0, scr_no = 0, total_score = 0;
    float average = 0.0;

    cout << "This program averages test scores." << endl << endl;
    
    cout << "For how many students do you have scores? ";
    cin >> std_no;

    cout << "How many test scores does each student have? ";
    cin >> scr_no;

    cout << endl;
    
    int i = 1, j = 1;

    
    while (j <= std_no)
    {
        i = 1;
        while (i <= scr_no)
        {
            int m = 0;
            cout << "Enter score " << i << " for student " << j << ": ";
            cin >> m;
            total_score += m;
            m = 0;
            
            i++;
        }

        average = float(total_score) / scr_no;
        cout << endl << endl << "The average of score for student " << j << " is: " << average;
        cout << endl << endl;

        average = 0;
        total_score = 0;
        j++;
    }
    
    return 0;
}
