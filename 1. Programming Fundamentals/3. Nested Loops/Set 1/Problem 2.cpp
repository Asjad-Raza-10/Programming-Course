#include <iostream>
using namespace std;
int main()
{
    int i = 0;

    cout << "Prime numbers from 1 to 300 are: " << endl;
    for(i = 2; i < 301; i++)
    {
        int flag = 1;
        for(int j = 2; j <= i; j++)
        {
            if(j == i)
            {
                if(i % j != 0)
                {
                    flag = 0;
                }
                continue;
            }

            if(i % j == 0)
            {
                flag = 0;
            }
        }
        if(flag == 1)
        {
            cout << i << " ";
        }

    }

    return 0;
}