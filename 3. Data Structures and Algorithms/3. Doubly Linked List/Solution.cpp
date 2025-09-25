#include <iostream>
using namespace std;

template<typename T>
class Node
{
public:
    T data;
    Node* prev;
    Node* next;

    Node(T d)
    {
        data = d;
        prev = next = nullptr;
    }
};

template <typename T>
class DLL 
{
private:
    Node<T>* head;
    Node<T>* tail;
    
public:
    DLL()
    {
        head = tail = nullptr;
    }

    void InsertAtBeginning(T data)
    {
        Node<T>* temp = new Node<T>(data);
        if (!head)
        {
            head = tail = temp;
            return;
        }
        temp->next = head;
        head->prev = temp;
        temp->prev = nullptr;
        head = temp;
    }

    void InsertAtEnd(T data)
    {
        Node<T>* temp = new Node<T>(data);

        if (!head)
        {
            head = tail = temp;
            return;
        }

        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }

    void InsertAtPosition(int index, T data)
    {
        if (index < 0)
        {
            throw out_of_range("Index Out of Bound");
        }

        if (!index)
        {
            InsertAtBeginning(data);
            return;
        }

        Node<T>* temp = new Node<T>(data);
        Node<T>* traverse = head;


        while (index > 0)
        {
            traverse = traverse->next;
            if (!traverse)
            {
                throw out_of_range("Index Out of Bound");
            }
            index--;
        }

        temp->next = traverse;
        temp->prev = traverse->prev;
        traverse->prev->next = temp;
        traverse->prev = temp;
    }

    void DeleteFromtEnd()
    {
        if (!head)
        {
            return;
        }

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }

        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;

    }

    void DeleteFromBeginning()
    {
        if (!head)
        {
            return;
        }

        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }

        head = head->next;
        delete head->prev;
        head->prev = nullptr;
    }

    void DeleteValue(T data)
    {
        Node<T>* traverse = head;

        while (traverse)
        {
            if (traverse->data == data)
            {
                if (traverse == head)
                {
                    DeleteFromBeginning();
                    return;
                }
                else if (!traverse->next)
                {
                    DeleteFromtEnd();
                    return;
                }
                else
                {
                    traverse->prev->next = traverse->next;
                    traverse->next->prev = traverse->prev;
                    delete traverse;
                }
            }
            traverse = traverse->next;
        }

    }

    void traverse_forward()
    {
        Node<T>* temp = head;

        if (!temp)
        {
            cout << "List is Empty!" << endl;
            return;
        }

        cout << "Traversing Forward: ";

        while (temp)
        {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }

    }

    void traverse_backward()
    {
        Node<T>* temp = tail;

        if (!temp)
        {
            cout << "List is Empty!" << endl;
            return;
        }

        cout << endl << "Traversing Backward: ";

        while (temp)
        {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
    }

    int search(T data)
    {
        Node<T>* traverse = head;
        int c = 0;

        while (traverse)
        {
            if (traverse->data == data)
            {
                return c;
            }
            traverse = traverse->next;
            c++;
        }

        return -1;
    }
};

class PlayList
{
private:
    DLL<string> song;

public:
    PlayList()
    {
    }
    void AddSongAtTheEnd(string s)
    {
        song.InsertAtEnd(s);
    }

    void DeleteSong(string s)
    {
        song.DeleteValue(s);
    }

    void ShowPlayListForward()
    {
        song.traverse_forward();
    }

    void ShowPlayListBackward()
    {
        song.traverse_backward();
    }
};

// main

int main()
{
    cout << " ======= TASK 1 =======" << endl << endl;

    Node<int>* N1 = new Node<int>(5);
    Node<int>* N2 = new Node<int>(7);
    Node<int>* N3 = new Node<int>(12);

    N1->next = N2;
    N2->prev = N1;

    N2->next = N3;
    N3->prev = N2;

    Node<int>* temp = N1;

    cout << "Nodes: ";

    while (temp)
    {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }

    temp = N3;

    cout << endl << "Nodes in Reverse Order: ";

    while (temp)
    {
        cout << temp->data << " <-> ";
        temp = temp->prev;
    }

    cout << endl << endl << " ======= TASK 3 - 4 =======" << endl << endl;

    DLL<int> doublylinkedlist;
    
    doublylinkedlist.traverse_forward();
    
    doublylinkedlist.InsertAtBeginning(5);
    doublylinkedlist.InsertAtBeginning(1);
    doublylinkedlist.InsertAtEnd(12);
    try 
    {
        doublylinkedlist.InsertAtPosition(-1, 7);
    }
    catch (exception & e)
    {
        cout << e.what();
    }
    
    cout << endl << "After Inserting Elements" << endl;
    doublylinkedlist.traverse_forward();
    
    doublylinkedlist.DeleteValue(1);
    
    cout << endl << endl << "After Deleting by Value = 1" << endl;
    doublylinkedlist.traverse_forward();

    cout << endl << endl <<"Searching Index for Value = 5: " << doublylinkedlist.search(5) << endl << endl;
    
    doublylinkedlist.traverse_forward();
    doublylinkedlist.traverse_backward();

    cout << endl << endl << " ======= TASK 5 =======" << endl << endl;

    PlayList MyPlayList;

    MyPlayList.AddSongAtTheEnd("Saiyaara");
    MyPlayList.AddSongAtTheEnd("Afsanay");
    MyPlayList.AddSongAtTheEnd("Faasle");
    MyPlayList.AddSongAtTheEnd("Humsafar");

    MyPlayList.ShowPlayListForward();

    MyPlayList.DeleteSong("Saiyaara");

    cout << endl << endl << "After Deleting Song = Saiyaara" << endl;
    MyPlayList.ShowPlayListForward();
    cout << endl;
    MyPlayList.ShowPlayListBackward();

    cout << endl;

    return 0;
}

