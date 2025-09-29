#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <class T> class Stack
{
    T *arr;
    int capacity;
    int current;

  public:
    Stack(int n = 5)
    {
        capacity = n;
        arr = new T[capacity];
        current = -1;
    }

    bool isEmpty()
    {
        if (current == -1)
            return true;
        return false;
    }

    bool isFull()
    {
        if (current == capacity - 1)
            return true;
        return false;
    }

    void push(T d)
    {
        if (isFull())
        {
            cerr << "Stack is full!" << endl;
        }
        else
        {
            arr[++current] = d;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }

        return arr[current--];
    }

    T top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        return arr[current];
    }

    void print()
    {
        for (int i = current; i >= 0; i--)
        {
            cout << arr[i] << endl;
        }
    }
};

int main()
{
    ifstream file(
        "/Volumes/Data/Portfolio/Github/Programming Course/3. Data Structures and Algorithms/6. Stacks/test.xml");
    // open the file
    if (!file.is_open())
    {
        cout << "Error: Could not open file!" << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line)) // read line by line
    {
        lineNumber++;
        cout << "Line " << lineNumber << ": " << line << endl;
    }

    file.close();
    return 0;
}
