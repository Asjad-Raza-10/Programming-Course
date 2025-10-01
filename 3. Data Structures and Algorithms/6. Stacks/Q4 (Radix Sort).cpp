#include <cctype>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

template <typename T> class Queue
{
  private:
    int Size;
    T *arr;
    int front, rear;

    bool isFull()
    {
        return rear == Size - 1;
    }

  public:
    Queue(int s = 10)
    {
        Size = s;
        arr = new T[Size];
        front = rear = -1;
    }

    bool isEmpty()
    {
        return front == -1;
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
            cout << "Queue is Full" << endl;
        }
    }

    T dequeue()
    {
        T temp;
        if (!isEmpty())
        {
            temp = arr[front];
            if (!rear) // rear is 0
            {
                front = rear = -1;
                return temp;
            }

            for (int i = 0; i <= rear - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            rear--;

            return temp;
        }

        cout << "Queue is empty" << endl;
        return temp;
    }

    void print()
    {
        cout << "QUEUE : " << arr[front];
        for (int i = front + 1; i <= rear; i++)
        {
            cout << " -> " << arr[i];
        }

        cout << endl;
    }

    T max()
    {
        if (isEmpty())
        {
            return T();
        }

        T max_element = arr[front];
        for (int i = front + 1; i <= rear; i++)
        {
            if (arr[i] > max_element)
            {
                max_element = arr[i];
            }
        }
        return max_element;
    }

    int getSize()
    {
        return rear + 1;
    }

    void convertToLowerCase()
    {
        for (int i = front; i <= rear; i++)
        {
            for (char &c : arr[i])
            {
                c = tolower(c);
            }
        }
    }

    ~Queue()
    {
        delete[] arr;
    }
};

int getLength(int n)
{
    int i = 0;
    while (n != 0)
    {
        i++;
        n /= 10;
    }
    return i;
}

void RadixSortInt(Queue<int> &input)
{
    // finding max element
    int max_element = input.max();
    int m = 10;                     // as int are from 0 to 9
    int k = getLength(max_element); // number of digits in greatest element
    int n = input.getSize();        // number of elements
    Queue<int> *radix = new Queue<int>[m];

    for (int p = 0; p < k; p++)
    {
        for (int i = 0; i < n; i++)
        {
            int num = input.dequeue();
            int temp = num;
            for (int j = 0; j < p; j++)
            {
                temp /= m;
            }
            int d = temp % m;

            radix[d].enqueue(num);
        }

        for (int i = 0; i < m; i++)
        {
            while (!radix[i].isEmpty())
            {
                input.enqueue(radix[i].dequeue());
            }
        }
    }

    delete[] radix;
}

void RadixSortStr(Queue<string> &input)
{
    // finding max element
    input.convertToLowerCase();

    // longest string length
    int k = 0;
    int n = input.getSize(); // number of elements
    for (int i = 0; i < n; i++)
    {
        string str = input.dequeue();
        if (str.length() > k)
        {
            k = str.length();
        }
        input.enqueue(str); // Put it back
    }

    int m = 26; // taking lowercase abc only
    Queue<string> *radix = new Queue<string>[m];

    for (int p = 0; p < k; p++)
    {
        for (int i = 0; i < n; i++)
        {
            string str = input.dequeue();
            string temp = str;

            // kth last character, array index, moving right to left
            int lastCharIndex = str.size() - p - 1;
            char lastChar = '\0';
            // to make it work for different length strings
            // if any string is shorter than p (max length string)
            if (lastCharIndex >= 0)
            {
                lastChar = str[lastCharIndex];
            }
            else
            {
                // the -a at end will complement it
                lastChar = 'a';
            }
            // ASCII of last char - a to get appropriate index bw 0 & 26
            int d = lastChar - 'a';
            radix[d].enqueue(str);
        }

        for (int i = 0; i < m; i++)
        {
            while (!radix[i].isEmpty())
            {
                input.enqueue(radix[i].dequeue());
            }
        }
    }

    delete[] radix;
}

int main()
{
    Queue<int> inputInt;
    // 802, 2, 24, 45, 66, 170, 75
    inputInt.enqueue(802);
    inputInt.enqueue(2);
    inputInt.enqueue(24);
    inputInt.enqueue(45);
    inputInt.enqueue(66);
    inputInt.enqueue(170);
    inputInt.enqueue(75);

    cout << endl << "Integer Queue before Radix Sort: ";
    inputInt.print();

    RadixSortInt(inputInt);

    cout << "Integer Queue after Radix Sort: ";
    inputInt.print();

    Queue<string> inputStr;
    // "bat", "apple", "dog", "ant"
    inputStr.enqueue("bat");
    inputStr.enqueue("apple");
    inputStr.enqueue("dog");
    inputStr.enqueue("ant");

    cout << endl << endl << "String Queue before Radix Sort: ";
    inputStr.print();

    RadixSortStr(inputStr);

    cout << "String Queue after Radix Sort: ";
    inputStr.print();

    return 0;
}