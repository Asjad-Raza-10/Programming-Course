#include <iostream>

using namespace std;

// Part 2 Task 1

template <class T> class StackWithArray
{
    T *arr;
    int capacity;
    int current;

  public:
    StackWithArray(int n = 5)
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

    T peek()
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
        cout << "Stack with Array: ";

        if (current == -1)
        {
            cout << "EMPTY" << endl;
        }

        for (int i = current; i >= 0; i--)
        {
            cout << endl << arr[i];
        }
        cout << endl;
    }

    ~StackWithArray()
    {
        delete[] arr;
    }
};

// Part 2 Task 2

template <typename T> class StackWithLinkedList
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
    StackWithLinkedList()
    {
        front = rear = nullptr;
    }

    StackWithLinkedList(T num)
    {
        Node *n = new Node(num);
        front = rear = n;
    }

    void push(T d)
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

    T pop()
    {
        if (!front)
        {
            return T();
        }

        T temp = rear->data;

        if (front == rear)
        {
            delete front;
            front = rear = nullptr;
            return temp;
        }

        Node *move = front;
        Node *prev = nullptr;

        while (move)
        {
            if (!move->next)
            {
                delete rear;
                rear = prev;
                rear->next = nullptr;
                break;
            }

            prev = move;
            move = move->next;
        }

        return temp;
    }

    void print()
    {
        cout << endl << "Stack with Linked List is: ";
        Node *temp = front;

        cout << temp->data;
        temp = temp->next;

        while (temp)
        {
            cout << " <- " << temp->data;

            temp = temp->next;
        }

        cout << endl << endl;
    }

    bool isEmpty()
    {
        return !front;
    }

    T peek()
    {
        return rear->data;
    }

    ~StackWithLinkedList()
    {
        while (front)
        {
            Node *move = front;
            front = front->next;
            delete move;
        }
    }
};

// Part 3 Task 4

int evaluatePostfix(string expression)
{
    StackWithLinkedList<int> stack;

    for (char ch : expression)
    {
        if (ch >= '0' && ch <= '9')
        {
            stack.push(ch - '0'); // Convert char to int
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            int operand2 = stack.pop();
            int operand1 = stack.pop();

            int result;
            if (ch == '+')
            {
                result = operand1 + operand2;
            }
            else if (ch == '-')
            {
                result = operand1 - operand2;
            }
            else if (ch == '*')
            {
                result = operand1 * operand2;
            }
            else if (ch == '/')
            {
                result = operand1 / operand2;
            }

            stack.push(result);
        }
    }

    return stack.pop();
}

// Part 3 Task 5

int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/')
    {
        return 2;
    }
    return 0;
}

string infixToPostfix(string infix)
{
    StackWithLinkedList<char> stack;
    string postfix = "";

    for (char ch : infix)
    {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            stack.push(ch);
        }
        else if (ch == ')')
        {
            while (!stack.isEmpty() && stack.peek() != '(')
            {
                postfix += stack.pop();
            }
            stack.pop(); // Remove '(' from stack
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            // check precedence
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch))
            {
                postfix += stack.pop();
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty())
    {
        postfix += stack.pop();
    }

    return postfix;
}

// Part 6

template <class T> class SpecialStack
{
    T *arr;
    int capacity;
    int current;
    int min;
    StackWithArray<T> MinStack;

  public:
    SpecialStack(int n = 5)
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
            if (current == -1)
            {
                min = d;
                MinStack.push(min);
            }
            else
            {
                if (d < min)
                {
                    min = d;
                    MinStack.push(min);
                }
            }
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

        if (arr[current] == min)
        {
            MinStack.pop();
            return arr[current--];
        }

        min = MinStack.pop();
    }

    T getMin()
    {
        if (isEmpty())
        {
            return T();
        }
        return min;
    }

    T peek()
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
        cout << "Special Stack: " << endl;
        for (int i = current; i >= 0; i--)
        {
            cout << arr[i] << endl;
        }
    }

    ~SpecialStack()
    {
        delete[] arr;
    }
};

// Part 3 Task 3

bool CheckString(string str)
{
    StackWithArray<char> S;

    char r = '\0';

    for (char c : str)
    {
        if (c == '{' || c == '[' || c == '(')
        {
            S.push(c);
        }
        if (c == '}' || c == ']' || c == ')')
        {
            r = S.pop();
            if (r == '(')
            {
                if (c != ')')
                {
                    return false;
                }
            }
            else if (r == '[')
            {
                if (c != ']')
                {
                    return false;
                }
            }
            else if (r == '{')
            {
                if (c != '}')
                {
                    return false;
                }
            }
        }
    }
    return true;
}

// Part 4 Task 6:

void ShowUndoRedo()
{
    StackWithArray<string> Undo;
    StackWithArray<string> Redo;

    cout << endl << "Initial Stacks: " << endl;
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    string str = "Asjad";
    cout << "User typed: " << str << endl;
    Undo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    str = "Raza";
    cout << "User typed: " << str << endl;
    Undo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    str = "Ali";
    cout << "User typed: " << str << endl;
    Undo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    cout << "User did Undo, \"" << str << "\" removed" << endl;
    str = Undo.pop();
    Redo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    cout << "User did Undo again, \"Raza\" removed" << endl;
    str = Undo.pop();
    Redo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    cout << "User did Redo, \"Raza\" added again" << endl;
    str = Redo.pop();
    Undo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
    cout << endl;

    cout << "User did Redo again, \"Ali\" added again" << endl;
    str = Redo.pop();
    Undo.push(str);
    cout << "Undo: ";
    Undo.print();
    cout << "Redo: ";
    Redo.print();
}

// Part 4 Task 7:

void ShowBackNextPage()
{
    StackWithArray<string> Back;
    StackWithArray<string> Forward;
    string currentPage;

    cout << endl << "Initial Stacks: " << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    currentPage = "google.com";
    cout << "User visited: " << currentPage << endl;
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    cout << "User visited: facebook.com" << endl;
    Back.push(currentPage); // Save current page to back stack
    currentPage = "facebook.com";
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    cout << "User visited: youtube.com" << endl;
    Back.push(currentPage);
    currentPage = "youtube.com";
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    cout << "User clicked BACK button" << endl;
    Forward.push(currentPage); // Save current page
    currentPage = Back.pop();  // Get previous page
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    cout << "User clicked BACK button again" << endl;
    Forward.push(currentPage);
    currentPage = Back.pop();
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    cout << "User clicked FORWARD button" << endl;
    Back.push(currentPage);
    currentPage = Forward.pop();
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
    cout << endl;

    cout << "User clicked FORWARD button again" << endl;
    Back.push(currentPage);
    currentPage = Forward.pop();
    cout << "Current Page: " << currentPage << endl;
    cout << "Back: ";
    Back.print();
    cout << "Forward: ";
    Forward.print();
}

int main()
{
    StackWithArray<int> SA;
    StackWithLinkedList<int> SL;
    SpecialStack<int> SS;

    cout << "Part 2 Task 1: " << endl;
    SA.push(5);
    SA.push(10);

    SA.print();

    cout << "Part 2 Task 2: " << endl;
    SL.push(7);
    SL.push(9);

    SL.print();

    cout << "Part 6: " << endl;
    SS.push(5);
    SS.push(3);
    SS.push(7);
    SS.push(9);

    SS.print();

    cout << "Minimum Element in O(1): " << SS.getMin() << endl;

    cout << "Part 3 Task 3: " << endl;
    string inputStr1 = "{[()]}";
    string inputStr2 = "{[})(}";

    cout << inputStr1 << " is " << (CheckString(inputStr1) ? "Balanced" : "Not Balanced") << endl;
    cout << inputStr2 << " is " << (CheckString(inputStr2) ? "Balanced" : "Not Balanced") << endl;

    cout << endl << endl << "Part 4 Task 6: " << endl << endl;
    ShowUndoRedo();

    cout << endl << endl << "Part 4 Task 7: " << endl << endl;
    ShowBackNextPage();

    cout << endl << endl << "Part 3 Task 4: " << endl << endl;
    string postfix = "23*54*+9-";
    cout << "Postfix Expression: " << postfix << endl;

    int result = evaluatePostfix(postfix);
    cout << "Result: " << result << endl;

    cout << endl << "Part 3 Task 5: " << endl << endl;
    string infix = "(A+B)*C";
    cout << "Infix Expression: " << infix << endl;

    string postfixResult = infixToPostfix(infix);
    cout << "Postfix Expression: " << postfixResult << endl << endl << endl;
}
