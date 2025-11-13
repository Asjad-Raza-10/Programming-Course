#include <iostream>
#include <limits>
using namespace std;

void getNumInput(int &num)
{
    while (!(cin >> num) || (num < 0))
    {
        cout << "Invalid input. Please enter a positive integer: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

template <typename T> class QueuewithArray
{
  private:
    int Size;
    T *arr;
    int front, rear;

    bool isFull()
    {
        return rear == Size - 1;
    }

    bool isHalf()
    {
        return (rear <= (Size / 2 - 1));
    }

    bool isEmpty()
    {
        return front == -1;
    }

    void grow()
    {
        int new_Size = Size * 2;
        T *temp = new T[new_Size];

        for (int i = 0; i < Size; i++)
        {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        Size = new_Size;
    }

    void shrink()
    {
        int new_Size = Size / 2;
        T *temp = new T[new_Size];

        for (int i = 0; i < Size; i++)
        {
            temp[i] = arr[i];
        }

        delete[] arr;
        arr = temp;
        Size = new_Size;
    }

  public:
    QueuewithArray(int s = 5)
    {
        Size = s;
        arr = new T[Size];
        front = rear = -1;

        cout << "A queue with size " << Size << " was created" << endl;
    }

    void enqueue(T data)
    {
        if (isEmpty())
        {
            front++;
        }

        if (!isFull())
        {
            arr[++rear] = data;
        }
        else
        {
            grow();
            arr[++rear] = data;
        }
    }

    void dequeue()
    {
        if (!isEmpty())
        {
            cout << arr[front] << " removed" << endl;
            for (int i = 0; i <= rear - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            rear--;
            if (isHalf())
            {
                shrink();
            }
            return;
        }

        cout << "Queue is empty" << endl;
    }

    void print()
    {
        cout << "QUEUE : ";
        for (int i = front; i <= rear; i++)
        {
            cout << arr[i] << " -> ";
        }

        cout << endl;
    }

    ~QueuewithArray()
    {
        delete[] arr;
    }
};

template <typename T> class CircularQueuewithArray
{
  private:
    int Size;
    T *arr;
    int front, rear;

    bool isFull()
    {
        return (rear + 1) % Size == front;
    }

    bool isEmpty()
    {
        return front == -1;
    }

  public:
    CircularQueuewithArray(int s = 5)
    {
        Size = s;
        arr = new T[Size];
        front = rear = -1;

        cout << "A queue with size " << Size << " was created" << endl;
    }

    void enqueue(T data)
    {
        if (isFull())
        {
            cout << "Cannot add " << data << endl;
            cout << "Queue is already full." << endl;
            return;
        }

        if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % Size;
        }

        arr[rear] = data;
        cout << data << " added." << endl;
    }

    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }

        cout << arr[front] << " removed." << endl;

        if (front == rear)
        {
            front = rear = -1;
            cout << "The Queue is now empty after the last element removal. " << endl;
        }
        else
        {
            front = (front + 1) % Size;
        }
    }

    void print()
    {
        cout << "QUEUE : ";
        if (isEmpty())
        {
            cout << "EMPTY" << endl;
            return;
        }
        int i = front;
        do
        {
            cout << arr[i] << " -> ";
            i = (i + 1) % Size;
        } while (i != (rear + 1) % Size);

        cout << endl;
    }

    ~CircularQueuewithArray()
    {
        delete[] arr;
    }
};

template <typename T> class QueueWithLinkedList
{
  private:
    class Node
    {
      public:
        Node *next;
        T data;

        Node()
        {
            next = nullptr;
        }

        Node(T d)
        {
            next = nullptr;
            data = d;
        }
    };

    Node *front;
    Node *rear;

  public:
    QueueWithLinkedList()
    {
        front = rear = nullptr;
    }

    QueueWithLinkedList(T num)
    {
        Node *n = new Node(num);
        front = rear = n;
    }

    void enqueue(T d)
    {
        Node *n = new Node(d);
        if (!front)
        {
            front = rear = n;
            return;
        }

        rear->next = n;
        rear = n;
    }

    void dequeue()
    {
        if (!front)
        {
            return;
        }
        if (front == rear)
        {
            front = rear = nullptr;
            return;
        }

        Node *temp = front->next;
        delete front;
        front = temp;
    }

    void print()
    {
        cout << endl << "Queue: ";
        if (!front)
        {
            cout << "EMPTY" << endl;
            return;
        }

        Node *temp = front;

        cout << temp->data;
        temp = temp->next;

        while (temp)
        {
            cout << " -> " << temp->data;

            temp = temp->next;
        }

        cout << endl << endl;
    }

    ~QueueWithLinkedList()
    {
        while (front)
        {
            Node *move = front;
            front = front->next;
            delete move;
        }
    }
};

int main()
{
    int choice;

    do
    {
        cout << "============ MENU ============" << endl;
        cout << endl << "Choose type of Queue" << endl;
        cout << "1. Queue using Array" << endl;
        cout << "2. Queue using Linked List" << endl;
        cout << "3. Circular Queue using Array" << endl;
        cout << "4. Exit the Program" << endl;

        cout << endl << "Enter choice: ";
        cin >> choice;

        int inner_choice;

        switch (choice)
        {
        case 1: {
            QueuewithArray<int> qwa;
            do
            {
                cout << endl << endl << "--------- QUEUE USING ARRAY ---------" << endl;
                cout << endl << "Choose type of Operation" << endl;
                cout << "1. Enqueue (Add element)" << endl;
                cout << "2. Dequeue (Remove Element)" << endl;
                cout << "3. Display Queue" << endl;
                cout << "4. Go Back to Main Menu" << endl;

                cout << endl << "Enter choice: ";
                cin >> inner_choice;

                switch (inner_choice)
                {
                case 1:
                    int d;
                    cout << "Enter Data to Add: ";
                    getNumInput(d);
                    qwa.enqueue(d);
                    break;

                case 2:
                    qwa.dequeue();
                    break;

                case 3:
                    qwa.print();
                    break;

                case 4:
                    break;

                default:
                    cout << "Invalid input. Please enter an integer: " << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << endl << endl;
            } while (inner_choice != 4);

            break;
        }

        case 2: {
            QueueWithLinkedList<int> qwll;
            do
            {
                cout << endl << endl << "--------- QUEUE USING LINKED LIST ---------" << endl;
                cout << endl << "Choose type of Operation" << endl;
                cout << "1. Enqueue (Add element)" << endl;
                cout << "2. Dequeue (Remove Element)" << endl;
                cout << "3. Display Queue" << endl;
                cout << "4. Go Back to Main Menu" << endl;

                cout << endl << "Enter choice: ";
                cin >> inner_choice;

                switch (inner_choice)
                {
                case 1:
                    int d;
                    cout << "Enter Data to Add: ";
                    getNumInput(d);
                    qwll.enqueue(d);
                    break;

                case 2:
                    qwll.dequeue();
                    break;

                case 3:
                    qwll.print();
                    break;

                case 4:
                    break;

                default:
                    cout << "Invalid input. Please enter an integer: " << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << endl << endl;
            } while (inner_choice != 4);

            break;
        }

        case 3: {
            CircularQueuewithArray<int> cqwa;
            do
            {
                cout << endl << endl << "--------- CIRCULAR QUEUE USING ARRAY ---------" << endl;
                cout << endl << "Choose type of Operation" << endl;
                cout << "1. Enqueue (Add element)" << endl;
                cout << "2. Dequeue (Remove Element)" << endl;
                cout << "3. Display Queue" << endl;
                cout << "4. Go Back to Main Menu" << endl;

                cout << endl << "Enter choice: ";
                cin >> inner_choice;

                switch (inner_choice)
                {
                case 1:
                    int d;
                    cout << "Enter Data to Add: ";
                    getNumInput(d);
                    cqwa.enqueue(d);
                    break;

                case 2:
                    cqwa.dequeue();
                    break;

                case 3:
                    cqwa.print();
                    break;

                case 4:
                    break;

                default:
                    cout << "Invalid input. Please enter an integer: " << endl << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                cout << endl << endl;
            } while (inner_choice != 4);

            break;
        }

        case 4: {
            cout << "Exiting..." << endl;
            break;
        }

        default: {
            cout << "Invalid input. Please enter an integer: " << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        }
        cout << endl << endl;
    } while (choice != 4);

    return 0;
}