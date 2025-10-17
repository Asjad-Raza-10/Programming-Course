#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <typename T> class BT
{
  private:
    class Node
    {
      public:
        Node *left;
        Node *right;
        T data;

        Node(T d)
        {
            data = d;
            left = right = nullptr;
        }
    };

    Node *root;

    void inOrder(Node *p)
    {
        if (!p)
        {
            return;
        }
        inOrder(p->left);
        cout << p->data << " - ";
        inOrder(p->right);
    }

    void preOrder(Node *p)
    {
        if (!p)
        {
            return;
        }
        cout << p->data << " - ";
        preOrder(p->left);
        preOrder(p->right);
    }

    void postOrder(Node *p)
    {
        if (!p)
        {
            return;
        }
        postOrder(p->left);
        postOrder(p->right);
        cout << p->data << " - ";
    }

    void clear(Node *p)
    {
        if (!p)
        {
            return;
        }
        clear(p->left);
        clear(p->right);
        delete p;
    }

    bool searchHelp(Node *p, T d, int &count)
    {
        if (!p)
        {
            return false;
        }
        count++;

        return searchHelp(p->left, d, count) || searchHelp(p->right, d, count) || d == p->data;
    }

    // recursive Insert
    Node *recusiveInsertHelper(Node *temp, T data)
    {
        if (!temp)
        {
            return new Node(data);
        }
        if (temp->data < data)
        {
            temp->right = recusiveInsertHelper(temp->right, data);
        }
        else if (temp->data > data)
        {
            temp->left = recusiveInsertHelper(temp->left, data);
        }
        return temp;
    }

    int leafCount(Node *p)
    {
        if (!p->left && !p->right)
        {
            return 1;
        }
        return leafCount(p->left) + leafCount(p->right);
    }

    void rev(Node *p)
    {
        if (!p)
        {
            return;
        }
        swap(p->left, p->right);
        rev(p->left);
        rev(p->right);
    }

    int height(Node *p)
    {
        if (!p)
        {
            return 0;
        }
        return max((height(p->left) + 1), (height(p->right) + 1));
    }

  public:
    BT()
    {
        root = nullptr;
    }

    // iterative insert

    void Insert(T d)
    {
        if (!root)
        {
            root = new Node(d);
            return;
        }
        Node *temp = root;
        while (true)
        {
            if (d > temp->data)
            {
                if (!temp->right)
                {
                    temp->right = new Node(d);
                    return;
                }
                else
                {
                    temp = temp->right;
                }
            }
            else if (d < temp->data)
            {
                if (!temp->left)
                {
                    temp->left = new Node(d);
                    return;
                }
                else
                {
                    temp = temp->left;
                }
            }
            else
            {
                return;
            }
        }
    }

    // recursive Insert

    void recursiveInsert(T d)
    {
        root = recusiveInsertHelper(root, d);
    }

    void inOrderTraversal()
    {
        cout << endl << "In Order Traversal: ";
        if (!root)
        {
            cout << "Tree is Empty" << endl;
            return;
        }
        inOrder(root);
        cout << endl << endl;
    }

    void preOrderTraversal()
    {
        cout << endl << "Pre Order Traversal: ";
        if (!root)
        {
            cout << "Tree is Empty" << endl;
            return;
        }
        preOrder(root);
        cout << endl << endl;
    }

    void postOrderTraversal()
    {
        cout << endl << "Post Order Traversal: ";
        if (!root)
        {
            cout << "Tree is Empty" << endl;
            return;
        }
        postOrder(root);
        cout << endl << endl;
    }

    bool search(T d, int &count)
    {
        if (!root)
        {
            return false;
        }
        return searchHelp(root, d, count);
    }

    int getHeight()
    {
        return height(root);
    }

    int getLeafCount()
    {
        return leafCount(root);
    }

    void reverse()
    {
        rev(root);
    }

    ~BT()
    {
        clear(root);
    }
};

int main()
{
    // Part 1

    cout << endl << " ======= PART 1 ======= " << endl;

    BT<int> t;

    t.Insert(1);
    t.Insert(2);
    t.Insert(3);
    t.Insert(4);
    t.Insert(5);

    t.inOrderTraversal();
    t.preOrderTraversal();
    t.postOrderTraversal();

    ifstream file("unique_human_names.txt");
    BT<string> names;
    string line;

    if (!file)
    {
        cerr << "Error: Could not open the fie!" << endl;
    }
    else
    {
        while (getline(file, line))
        {
            names.Insert(line);
        }
    }

    cout << endl << "Displaying Names read from the file" << endl;

    names.inOrderTraversal();
    names.preOrderTraversal();
    names.postOrderTraversal();

    file.close();

    // Part 2

    cout << endl << " ======= PART 2 ======= " << endl;

    BT<int> t1;
    t1.Insert(50);
    t1.Insert(30);
    t1.Insert(70);
    t1.Insert(20);
    t1.Insert(40);
    t1.Insert(60);
    t1.recursiveInsert(80);

    t1.inOrderTraversal();

    int count = 0;
    cout << endl
         << "Searching for 70: " << (t1.search(70, count) ? "Found" : "Not Found") << " Number of Steps: " << count
         << endl;
    count = 0;
    cout << endl
         << "Searching for 15: " << (t1.search(15, count) ? "Found" : "Not Found") << " Number of Steps: " << count
         << endl;
    count = 0;

    // Part 3

    cout << endl << " ======= PART 3 ======= " << endl;

    cout << endl << "Height of tree: " << t1.getHeight() << endl;
    cout << endl << "Number of leafs: " << t1.getLeafCount() << endl;

    // Part 4

    cout << endl << " ======= PART 4 ======= " << endl;
    cout << endl << "Before Mirror: ";
    t1.inOrderTraversal();
    t1.reverse();
    cout << "After Mirror: ";
    t1.inOrderTraversal();

    return 0;
}