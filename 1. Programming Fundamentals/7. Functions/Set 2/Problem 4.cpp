#include <iostream>
using namespace std;

void input(char str[100])
{
    cout << "Enter a string: ";
    cin.getline(str, 100);
}

int find_size(char str[100])
{
    int i = 0;
    while (str[i] != NULL)
    {
        i++;
    }
    return i;
}

void reverse(char str[100], int size)
{
    for (int i = 0; i < size/2; i++)
    {
        int temp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = temp;
    }
}

void disp(char str[100], int size)
{
    cout << "The reversed string is: ";
    for (int i = 0; i < size; i++)
    {
        cout << str[i];
    }
}

int main()
{
    char str[100] = { NULL };
    
    input(str);
    int size = find_size(str);
    reverse(str, size);
    disp(str, size);

    return 0;
}