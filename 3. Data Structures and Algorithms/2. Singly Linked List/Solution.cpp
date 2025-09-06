#include <iostream>

using namespace std;

template <typename T> class LinkedList
{
  private:
    friend class Polynomial;
    class Node
    {
        friend class Polynomial;

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

    Node *head;
    Node *tail;

  public:
    LinkedList()
    {
        head = tail = nullptr;
    }

    LinkedList(T num)
    {
        Node *n = new Node(num);
        head = tail = n;
    }

    void InsertAtBeginning(T d)
    {
        Node *n = new Node(d);
        if (!head)
        {
            head = tail = n;
            return;
        }

        n->next = head;
        head = n;
    }

    void InsertAtEnd(T d)
    {
        Node *n = new Node(d);
        if (!head)
        {
            head = tail = n;
            return;
        }

        tail->next = n;
        tail = n;
    }

    void InsertAtPosition(int pos, T val)
    {
        if (pos == 1)
        {
            InsertAtBeginning(val);
            return;
        }

        Node *n = new Node(val);
        Node *move = head;
        Node *prev = head;

        int i = 0;

        while (i < pos)
        {
            move = move->next;

            if (i != 0)
            {
                prev = prev->next;
            }

            i++;
        }

        n->next = move;
        prev->next = n;

        if (tail->next && !move->next)
        {
            tail = move;
        }
    }

    void DeleteFromBeginning()
    {
        if (!head)
        {
            return;
        }
        if (head == tail)
        {
            head = tail = nullptr;
            return;
        }

        Node *temp = head->next;
        delete head;
        head = temp;
    }

    void DeleteFromEnd()
    {
        if (!head)
        {
            return;
        }
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node *move = head;
        Node *prev = nullptr;

        while (move)
        {
            if (!move->next)
            {
                delete tail;
                tail = prev;
                tail->next = nullptr;
                break;
            }

            prev = move;
            move = move->next;
        }
    }

    void DeleteFromPosition(int pos)
    {
        if (pos == 1)
        {
            DeleteFromBeginning();
            return;
        }

        Node *move = head;
        Node *prev = head;

        int i = 0;

        while (i < pos)
        {
            move = move->next;

            if (i != 0)
            {
                prev = prev->next;
            }

            i++;
        }

        prev->next = move->next;
        delete move;

        if (!prev->next)
        {
            tail = prev;
        }
    }

    void DeleteByValue(T value)
    {
        int position = Search(value);

        if (position == -1)
        {
            return;
        }

        DeleteFromPosition(position);
    }

    int Search(T val)
    {
        Node *move = head;
        int i = 0;

        while (move)
        {
            if (move->data == val)
            {
                return i;
            }

            i++;
            move = move->next;
        }

        return -1;
    }

    void Reverse()
    {
        Node *prev = nullptr;
        Node *current = head;
        while (current)
        {
            Node *temp = current->next;
            current->next = prev;
            prev = current;
            current = temp;
        }
        Node *temp = head;
        head = tail;
        tail = temp;
    }

    void Display()
    {
        cout << endl << "Linked List is: ";
        Node *temp = head;

        cout << temp->data;
        temp = temp->next;

        while (temp)
        {
            cout << " -> " << temp->data;

            temp = temp->next;
        }

        cout << endl << endl;
    }

    int getSize()
    {
        Node *temp = head;
        int n = 0;
        while (temp)
        {
            n++;
            temp = temp->next;
        }
        return n;
    }

    ~LinkedList()
    {
        while (head)
        {
            Node *move = head;
            head = head->next;
            delete move;
        }
    }
};

class Polynomial
{
  private:
    LinkedList<int> lst;
    LinkedList<int>::Node *p = lst.head;

  public:
    Polynomial()
    {
    }

    void AddCoefficient(int n)
    {
        lst.InsertAtEnd(n);
    }

    void disp_assistant(LinkedList<int>::Node *head, int degree)
    {
        if (!head)
        {
            return;
        }

        if (head->next == nullptr)
        {
            cout << head->data << "x^" << degree;
            return;
        }

        disp_assistant(head->next, degree + 1);
        if (degree > 0)
        {
            cout << " + " << head->data << "x^" << degree;
        }
        else
        {
            cout << " + " << head->data;
        }
    }

    void display()
    {
        cout << endl << "The polynomial is: ";
        disp_assistant(lst.head, 0);

        cout << endl << endl;
    }

    Polynomial add(Polynomial &P)
    {
        Polynomial P3;

        LinkedList<int>::Node *P1_move = this->lst.head;
        LinkedList<int>::Node *P2_move = P.lst.head;
        // LinkedList<int>::Node *P3_move = P3.lst.head;

        while (P1_move || P2_move)
        {

            if (P1_move && P2_move)
            {
                int sum = 0;
                sum = P1_move->data + P2_move->data;
                P3.lst.InsertAtEnd(sum);
            }
            else if (!P1_move)
            {
                P3.lst.InsertAtEnd(P2_move->data);
            }
            else if (!P2_move)
            {
                P3.lst.InsertAtEnd(P1_move->data);
            }

            if (P1_move)
            {
                P1_move = P1_move->next;
            }
            if (P2_move)
            {
                P2_move = P2_move->next;
            }
        }
        return P3;
    }
};

int main()
{
    LinkedList<int> list;
    list.InsertAtBeginning(10);
    list.InsertAtEnd(20);
    list.InsertAtEnd(25);
    list.InsertAtBeginning(5);
    list.InsertAtPosition(2, 15);
    list.InsertAtPosition(1, 1);

    list.Display();

    cout << "20 is at index: " << list.Search(20) << endl;

    list.Reverse();

    cout << endl << "Reversed List: ";
    list.Display();

    cout << "Deleting Value 1: ";
    list.DeleteByValue(1);
    list.Display();

    cout << "Deleting from End: ";
    list.DeleteFromEnd();
    list.Display();

    cout << "List Size: " << list.getSize() << endl;

    // Implementing the Polynomial through Linked List

    Polynomial P1;

    P1.AddCoefficient(3);
    P1.AddCoefficient(4);
    P1.AddCoefficient(5);
    P1.AddCoefficient(9);

    cout << "The polynomial 1 is: ";
    P1.display();

    Polynomial P2;

    P2.AddCoefficient(7);
    P2.AddCoefficient(8);
    P2.AddCoefficient(9);

    cout << "The polynomial 2 is: ";
    P2.display();

    Polynomial P3 = P1.add(P2);

    cout << "Result after adding both polynomials: " << endl;
    P3.display();

    return 0;
}