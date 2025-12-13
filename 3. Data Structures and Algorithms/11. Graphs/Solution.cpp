#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template <typename T> class LinkedList
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

    Node *head;
    Node *tail;

  public:
    class Iterator
    {
        Node *node;

      public:
        Iterator(Node *nd = nullptr)
        {
            node = nd;
        }

        Iterator &operator=(Node *pNode)
        {
            this->node = pNode;
            return *this;
        }

        // Prefix ++ overload
        Iterator &operator++()
        {
            if (node)
            {
                node = node->next;
            }
            return *this;
        }

        bool operator!=(const Iterator &nd)
        {
            return nd.node != this->node;
        }

        // get value
        T operator*()
        {
            return node->data;
        }
    };

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

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
        Node *temp = head;
        cout << "[" << temp->data;
        temp = temp->next;

        while (temp)
        {
            cout << " " << temp->data;
            temp = temp->next;
        }

        cout << "]\n";
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

class GraphUsingAdjMatrix
{
  private:
    int vertices;
    bool isDirected;
    int **adjM;

    bool isValid(int u, int v)
    {
        return !(u < 0 || u >= vertices || v < 0 || v >= vertices);
    }

    bool isEdge(int u, int v)
    {
        if (isValid(u, v))
        {
            return adjM[u][v];
        }
        return false;
    }

    void DFSUtils(int sv, bool *&flag)
    {
        flag[sv] = true;
        cout << sv << " ";
        for (int i = 0; i < vertices; i++)
        {
            if (!flag[i] && isEdge(sv, i))
            {
                DFSUtils(i, flag);
            }
        }
    }

  public:
    GraphUsingAdjMatrix(int v = 5, bool f = false)
    {
        vertices = v;
        isDirected = f;
        adjM = new int *[v];
        for (int i = 0; i < v; i++)
        {
            adjM[i] = new int[v]{0};
        }
    }

    void addEdge(int u, int v)
    {
        if (isValid(u, v))
        {
            adjM[u][v] = 1;
            if (!isDirected)
            {
                adjM[v][u] = 1;
            }
        }
        else
        {
            cerr << "Invalid Index! \n";
        }
    }

    void removeEdge(int u, int v)
    {
        if (isValid(u, v))
        {
            if (isEdge(u, v))
            {
                adjM[u][v] = 0;
                if (!isDirected)
                {
                    adjM[v][u] = 0;
                }
            }
        }
        else
        {
            cerr << "Invalid Index! \n";
        }
    }

    void displayPairWise()
    {
        cout << "\nEdges connections pair wise: \n";
        for (int i = 0; i < vertices; i++)
        {
            cout << i << ": ";
            for (int j = 0; j < vertices; j++)
            {
                if (adjM[i][j])
                {
                    cout << "[" << j << "] ";
                }
            }
            cout << endl;
        }
    }

    void displayAdjM()
    {
        cout << "\nThe Adjacency Matrix for the garph is: \n";
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                cout << adjM[i][j] << " ";
            }
            cout << endl;
        }
    }

    void DFS(int sv)
    {
        cout << "\nDFS Starting from the vertice " << sv << ": ";
        bool *flag = new bool[vertices]{0};
        DFSUtils(sv, flag);
        delete[] flag;
        cout << endl;
    }

    void BFS(int sv)
    {
        cout << "\nBFS Starting from the vertice " << sv << ": ";
        bool *flag = new bool[vertices]{0};
        queue<int> q;

        q.push(sv);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            flag[current] = true;
            cout << current << " ";
            for (int i = 0; i < vertices; i++)
            {
                if (!flag[i] && isEdge(current, i))
                {
                    q.push(i);
                }
            }
        }

        cout << endl;
        delete[] flag;
    }

    ~GraphUsingAdjMatrix()
    {
        for (int i = 0; i < vertices; i++)
        {
            delete[] adjM[i];
        }
        delete[] adjM;
    }
};

class GraphUsingAdjList
{
  private:
    int vertices;
    bool isDirected;
    LinkedList<int> *adjL;

    bool isValid(int u, int v)
    {
        return !(u < 0 || u >= vertices || v < 0 || v >= vertices);
    }

    bool isEdge(int u, int v)
    {
        if (isValid(u, v))
        {
            return adjL[u].Search(v) != -1;
        }
        return false;
    }

    void DFSUtils(int sv, bool *&flag)
    {
        flag[sv] = true;
        cout << sv << " ";
        for (auto i = adjL[sv].begin(); i != adjL[sv].end(); ++i)
        {
            if (!flag[*i] && isEdge(sv, *i))
            {
                DFSUtils(*i, flag);
            }
        }
    }

  public:
    GraphUsingAdjList(int v = 5, bool f = false)
    {
        vertices = v;
        isDirected = f;
        adjL = new LinkedList<int>[v];
    }

    void addEdge(int u, int v)
    {
        if (isValid(u, v))
        {
            adjL[u].InsertAtEnd(v);
            if (!isDirected)
            {
                adjL[v].InsertAtEnd(u);
            }
        }
        else
        {
            cerr << "Invalid Index! \n";
        }
    }

    void removeEdge(int u, int v)
    {
        if (isValid(u, v))
        {
            if (isEdge(u, v))
            {
                adjL[u].DeleteByValue(v);
                if (!isDirected)
                {
                    adjL[v].DeleteByValue(u);
                }
            }
        }
        else
        {
            cerr << "Invalid Index! \n";
        }
    }

    void displayPairWise()
    {
        cout << "\nEdges connections pair wise: \n";
        for (int i = 0; i < vertices; i++)
        {
            cout << i << ": ";
            adjL[i].Display();
            cout << endl;
        }
    }

    void DFS(int sv)
    {
        cout << "\nDFS Starting from the vertice " << sv << ": ";
        bool *flag = new bool[vertices]{0};
        DFSUtils(sv, flag);
        delete[] flag;
        cout << endl;
    }

    void BFS(int sv)
    {
        cout << "\nBFS Starting from the vertice " << sv << ": ";
        bool *flag = new bool[vertices]{0};
        queue<int> q;

        q.push(sv);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            flag[current] = true;
            cout << current << " ";
            for (auto i = adjL[current].begin(); i != adjL[current].end(); ++i)
            {
                if (!flag[*i] && isEdge(current, *i))
                {
                    q.push(*i);
                }
            }
        }

        cout << endl;
        delete[] flag;
    }

    ~GraphUsingAdjList()
    {
        delete[] adjL;
    }
};

int main()
{
    cout << "======== TASK 1,3,4 ======== \n";
    GraphUsingAdjMatrix graph(5, 0);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);

    graph.displayPairWise();
    graph.displayAdjM();

    graph.DFS(0);
    graph.BFS(0);

    cout << "\n======== TASK 2,3,4 ======== \n";
    GraphUsingAdjList graphL(5, 0);
    graphL.addEdge(0, 1);
    graphL.addEdge(0, 2);
    graphL.addEdge(1, 3);
    graphL.addEdge(2, 4);

    graphL.displayPairWise();

    graphL.DFS(0);
    graphL.BFS(0);

    return 0;
}