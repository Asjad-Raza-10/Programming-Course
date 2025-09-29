#include <iostream>
using namespace std;

template <class T> class Stack
{
    T *arr;
    int capacity;
    int top;

  public:
    Stack(int n = 5)
    {
        capacity = 7;
        arr = new T[capacity];
        top = -1;
    }

    bool isEmpty()
    {
        if (top == -1)
            return true;
        return false;
    }

    bool isFull()
    {
        if (top == capacity - 1)
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
            arr[++top] = d;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }

        return arr[top--];
    }

    T top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        return arr[top];
    }

    void print()
    {
        for (int i = top; i >= 0; i--)
        {
            cout << arr[i] << endl;
        }
    }
};

int main()
{

    return 0;
}