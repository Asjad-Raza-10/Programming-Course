#include <iostream>
using namespace std;

template <typename T> class CircularStack
{
  private:
    T *arr;
    int capacity;
    int top;
    bool flipped;

    bool isFull()
    {
        return (top == capacity - 1);
    }

    bool isEmpty()
    {
        return top == -1;
    }

    bool isHalf()
    {
        return (top <= (capacity / 2 - 1));
    }

    void grow()
    {
        int new_capacity = capacity * 2;
        T *temp = new T[new_capacity];

        for (int i = 0; i < capacity; i++)
        {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        capacity = new_capacity;

        cout << endl << endl << "The stack's capacity was increased to double" << endl << endl;
    }

    void shrink()
    {
        int new_capacity = capacity / 2;
        T *temp = new T[new_capacity];

        for (int i = 0; i < capacity; i++)
        {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        capacity = new_capacity;

        cout << endl << endl << "The stack's capacity was decreased to half" << endl << endl;
    }

  public:
    CircularStack(int s = 5)
    {
        capacity = s;
        arr = new T[capacity];
        top = -1;
        flipped = false;

        cout << "A stack with capacity " << capacity << " was created" << endl;
    }

    void push_normal(T data)
    {
        arr[++top] = data;
        cout << data << " added to the stack." << endl;
    }

    void push_flipped(T data)
    {
        // shift right, to make place at bottom
        top++;
        for (int i = top; i > 0; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[0] = data;
        cout << data << " added to the stack." << endl;
    }

    void push(T data)
    {
        if (isFull())
        {
            grow();
        }
        else
        {
            if (flipped)
            {
                push_flipped(data);
            }
            else
            {
                push_normal(data);
            }
        }
    }

    T pop_normal()
    {
        return arr[top--];
    }

    T pop_flipped()
    {
        T temp = arr[0];
        // shift left, to cover the extra space
        for (int i = 0; i < top; i++)
        {
            arr[i] = arr[i + 1];
        }
        top--;
        return temp;
    }

    T pop()
    {
        T temp;

        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return temp;
        }

        if (flipped)
        {
            temp = pop_flipped();
        }
        else
        {
            temp = pop_normal();
        }

        if (isHalf())
        {
            shrink();
        }

        return temp;
    }

    void print_normal()
    {
        for (int i = top; i >= 0; i--)
        {
            cout << endl << arr[i];
        }
    }

    void print_flipped()
    {
        for (int i = 0; i <= top; i++)
        {
            cout << endl << arr[i];
        }
    }

    void print()
    {
        cout << "Stack : ";
        if (isEmpty())
        {
            cout << "EMPTY" << endl;
        }
        else
        {
            if (flipped)
            {
                print_flipped();
            }
            else
            {
                print_normal();
            }
        }
        cout << endl << endl;
    }

    void flip()
    {
        flipped = !flipped;
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

    C1.print();

    cout << endl << "Flipping Now " << endl << endl;
    C1.flip();
    C1.print();

    C1.push(4);
    C1.push(5);

    C1.print();

    cout << C1.pop() << " popped" << endl;

    cout << endl << "Flipping Now " << endl << endl;
    C1.flip();

    C1.print();

    cout << C1.pop() << " popped" << endl;
    cout << C1.pop() << " popped" << endl;

    C1.push(45);
    C1.print();
}