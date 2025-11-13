#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Node structure for heap tree
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node *parent;

    Node(int val) : data(val), left(nullptr), right(nullptr), parent(nullptr)
    {
    }
};

class MaxHeap
{
  private:
    Node *root;
    int size;
    int curr;

    // Helper function to find the position for insertion (level-order)
    Node *findInsertPosition()
    {
        if (!root)
            return nullptr;

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();

            if (!temp->left || !temp->right)
                return temp;

            q.push(temp->left);
            q.push(temp->right);
        }
        return nullptr;
    }

    // Helper function to find the last node (for deletion)
    Node *findLastNode()
    {
        if (!root)
            return nullptr;

        queue<Node *> q;
        q.push(root);
        Node *lastNode = nullptr;

        while (!q.empty())
        {
            lastNode = q.front();
            q.pop();

            if (lastNode->left)
                q.push(lastNode->left);
            if (lastNode->right)
                q.push(lastNode->right);
        }
        return lastNode;
    }

    void heapifyUp(Node *node)
    {
        while (node->parent && node->data > node->parent->data)
        {
            swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    void heapifyDown(Node *node)
    {
        while (node)
        {
            Node *largest = node;

            if (node->left && node->left->data > largest->data)
                largest = node->left;

            if (node->right && node->right->data > largest->data)
                largest = node->right;

            if (largest != node)
            {
                swap(node->data, largest->data);
                node = largest;
            }
            else
            {
                break;
            }
        }
    }

    void printLevelOrder(Node *node)
    {
        if (!node)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            cout << temp->data << " ";

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }

    void destroyTree(Node *node)
    {
        if (!node)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

  public:
    MaxHeap(int s = 100) : root(nullptr), size(s), curr(0)
    {
    }

    void insert(int data)
    {
        if (curr >= size)
            return;

        Node *newNode = new Node(data);
        curr++;

        if (!root)
        {
            root = newNode;
            return;
        }

        Node *parent = findInsertPosition();
        newNode->parent = parent;

        if (!parent->left)
            parent->left = newNode;
        else
            parent->right = newNode;

        heapifyUp(newNode);
    }

    int deleteData()
    {
        if (!root)
            return -1;

        int maxVal = root->data;

        if (curr == 1)
        {
            delete root;
            root = nullptr;
            curr--;
            return maxVal;
        }

        Node *lastNode = findLastNode();
        root->data = lastNode->data;

        // Remove last node
        if (lastNode->parent)
        {
            if (lastNode->parent->right == lastNode)
                lastNode->parent->right = nullptr;
            else
                lastNode->parent->left = nullptr;
        }

        delete lastNode;
        curr--;

        heapifyDown(root);
        return maxVal;
    }

    void print()
    {
        cout << endl;
        if (!root)
        {
            cout << "Heap is empty" << endl;
            return;
        }
        printLevelOrder(root);
        cout << endl;
    }

    int getSize()
    {
        return curr;
    }

    ~MaxHeap()
    {
        destroyTree(root);
    }
};

class MinHeap
{
  private:
    Node *root;
    int size;
    int curr;

    Node *findInsertPosition()
    {
        if (!root)
            return nullptr;

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();

            if (!temp->left || !temp->right)
                return temp;

            q.push(temp->left);
            q.push(temp->right);
        }
        return nullptr;
    }

    Node *findLastNode()
    {
        if (!root)
            return nullptr;

        queue<Node *> q;
        q.push(root);
        Node *lastNode = nullptr;

        while (!q.empty())
        {
            lastNode = q.front();
            q.pop();

            if (lastNode->left)
                q.push(lastNode->left);
            if (lastNode->right)
                q.push(lastNode->right);
        }
        return lastNode;
    }

    void heapifyUp(Node *node)
    {
        while (node->parent && node->data < node->parent->data)
        {
            swap(node->data, node->parent->data);
            node = node->parent;
        }
    }

    void heapifyDown(Node *node)
    {
        while (node)
        {
            Node *smallest = node;

            if (node->left && node->left->data < smallest->data)
                smallest = node->left;

            if (node->right && node->right->data < smallest->data)
                smallest = node->right;

            if (smallest != node)
            {
                swap(node->data, smallest->data);
                node = smallest;
            }
            else
            {
                break;
            }
        }
    }

    void printLevelOrder(Node *node)
    {
        if (!node)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();
            cout << temp->data << " ";

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }

    void destroyTree(Node *node)
    {
        if (!node)
            return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

  public:
    MinHeap(int s = 100) : root(nullptr), size(s), curr(0)
    {
    }

    void insert(int data)
    {
        if (curr >= size)
            return;

        Node *newNode = new Node(data);
        curr++;

        if (!root)
        {
            root = newNode;
            return;
        }

        Node *parent = findInsertPosition();
        newNode->parent = parent;

        if (!parent->left)
            parent->left = newNode;
        else
            parent->right = newNode;

        heapifyUp(newNode);
    }

    int deleteData()
    {
        if (!root)
            return -1;

        int minVal = root->data;

        if (curr == 1)
        {
            delete root;
            root = nullptr;
            curr--;
            return minVal;
        }

        Node *lastNode = findLastNode();
        root->data = lastNode->data;

        if (lastNode->parent)
        {
            if (lastNode->parent->right == lastNode)
                lastNode->parent->right = nullptr;
            else
                lastNode->parent->left = nullptr;
        }

        delete lastNode;
        curr--;

        heapifyDown(root);
        return minVal;
    }

    void print()
    {
        cout << endl;
        if (!root)
        {
            cout << "Heap is empty" << endl;
            return;
        }
        printLevelOrder(root);
        cout << endl;
    }

    int getSize()
    {
        return curr;
    }

    ~MinHeap()
    {
        destroyTree(root);
    }
};

// Heap Sort Functions
void heapSortAscending(int *arr, int size)
{
    MaxHeap m(size);
    for (int i = 0; i < size; i++)
    {
        m.insert(arr[i]);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        arr[i] = m.deleteData();
    }
}

void heapSortDescending(int *arr, int size)
{
    MinHeap m(size);
    for (int i = 0; i < size; i++)
    {
        m.insert(arr[i]);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        arr[i] = m.deleteData();
    }
}

void buildMaxHeap(int *arr, int size, MaxHeap &mxH)
{
    for (int i = 0; i < size; i++)
    {
        mxH.insert(arr[i]);
    }
    cout << "Max Heap was built" << endl;
    cout << "Max Heap is:";
    mxH.print();
}

void buildMinHeap(int *arr, int size, MinHeap &mnH)
{
    for (int i = 0; i < size; i++)
    {
        mnH.insert(arr[i]);
    }
    cout << "Min Heap was built" << endl;
    cout << "Min Heap is:";
    mnH.print();
}

// Priority Queue Classes
class MinPriorityQueue
{
  private:
    MinHeap mnH;

  public:
    MinPriorityQueue(int size = 100) : mnH(size)
    {
    }

    void enqueue(int d)
    {
        mnH.insert(d);
    }

    int dequeue()
    {
        return mnH.deleteData();
    }

    void print()
    {
        cout << "Minimum Priority Queue is: ";
        mnH.print();
    }
};

class MaxPriorityQueue
{
  private:
    MaxHeap mxH;

  public:
    MaxPriorityQueue(int size = 100) : mxH(size)
    {
    }

    void enqueue(int d)
    {
        mxH.insert(d);
    }

    int dequeue()
    {
        return mxH.deleteData();
    }

    void print()
    {
        cout << "Maximum Priority Queue is: ";
        mxH.print();
    }
};

int main()
{
    // Question 1
    cout << endl << "======= Question 1 =======" << endl;
    int arr[6] = {30, 20, 40, 10, 50, 60};
    MaxHeap mxH(100);
    buildMaxHeap(arr, 6, mxH);

    cout << "Inserting 35" << endl;
    mxH.insert(35);
    cout << "Max Heap is:";
    mxH.print();

    cout << "Deleting root from Max Heap" << endl;
    cout << "Deleted value is : " << mxH.deleteData() << endl;
    cout << "Max heap now:";
    mxH.print();

    // Question 2
    cout << endl << "======= Question 2 =======" << endl;
    int arr2[6] = {9, 5, 4, 1, 7, 3};
    MinHeap mnH(100);
    buildMinHeap(arr2, 6, mnH);

    cout << "Inserting 2" << endl;
    mnH.insert(2);
    cout << "Min Heap is:";
    mnH.print();

    cout << "Deleting root from Min Heap" << endl;
    cout << "Deleted value is : " << mnH.deleteData() << endl;
    cout << "Min heap now:";
    mnH.print();

    // Question 3
    cout << endl << "======= Question 3 =======" << endl;
    int arr3[7] = {19, 3, 15, 7, 8, 23, 74};
    cout << "Array before Ascending Heap Sort: ";
    for (int i = 0; i < 7; i++)
    {
        cout << arr3[i] << " ";
    }
    heapSortAscending(arr3, 7);
    cout << endl << "Array after Ascending Heap Sort: ";
    for (int i = 0; i < 7; i++)
    {
        cout << arr3[i] << " ";
    }

    int arr4[7] = {10, 23, 5, 76, 8, 42, 11};
    cout << endl << endl << "Array before Descending Heap Sort: ";
    for (int i = 0; i < 7; i++)
    {
        cout << arr4[i] << " ";
    }
    heapSortDescending(arr4, 7);
    cout << endl << "Array after Descending Heap Sort: ";
    for (int i = 0; i < 7; i++)
    {
        cout << arr4[i] << " ";
    }

    // Question 4 - Priority Queues
    cout << endl << endl << "======= Question 4 =======" << endl;
    MinPriorityQueue minPQ(100);
    cout << "Testing Min Priority Queue" << endl;
    minPQ.enqueue(15);
    minPQ.enqueue(10);
    minPQ.enqueue(20);
    minPQ.print();

    cout << endl;
    return 0;
}