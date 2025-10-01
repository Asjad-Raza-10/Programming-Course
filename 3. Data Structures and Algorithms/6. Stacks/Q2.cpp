#include <iostream>
using namespace std;

template <typename T> class CircularStack
{
  private:
    T *arr;
    int capacity;
    int top;
    int bottom;
    bool flipped;

    bool isFull()
    {
        return (top == capacity - 1);
    }

    bool isEmpty()
    {
        return top == -1;
    }

  public:
    CircularStack(int s = 5)
    {
        capacity = s;
        arr = new T[capacity];
        top = -1;
        bottom = 0;
        flipped = 0;

        cout << "A stack with capacity  " << capacity << " was created" << endl;
    }

    void push(T data)
    {
        if (isFull())
        {
            cout << "Cannot add " << data << endl;
            cout << "Stack is already full." << endl;
        }
        else
        {
            arr[++top] = data;
            cout << data << " added to the stack." << endl;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        if (top != 0)
        {
            top--;
        }
        else
        {
            top++;
        }
        return arr[top];
    }

    void print()
    {
        cout << "Stack : ";
        if (isEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        // int i = bottom;
        // do
        // {
        //     cout << endl << arr[i];
        //     i = (i + 1) % capacity;
        // } while (i != (top + 1) % capacity);

        if (top > bottom)
        {
            for (int i = top; i >= bottom; i--)
            {
                cout << endl << arr[i];
            }
        }
        else
        {
            for (int i = top; i <= bottom; i++)
            {
                cout << endl << arr[i];
            }
        }

        cout << endl << endl;
    }

    void flip()
    {
        flipped = 1;
    }

    ~CircularStack()
    {
        delete[] arr;
    }
};

int main()
{
    CircularStack<int> C1;

    C1.push(1);
    C1.push(2);
    C1.push(3);
    C1.push(4);
    C1.push(5);

    C1.print();

    cout << endl << "Flipping Now " << endl << endl;
    C1.flip();

    C1.print();
}