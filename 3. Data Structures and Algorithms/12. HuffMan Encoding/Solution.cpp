#include <cmath> // for log2
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Updated Node to hold tree pointers (left/right)
class Node
{
  public:
    char data;
    int count;
    Node *left;
    Node *right;

    Node(char d = '\0', int c = 1)
    {
        data = d;
        count = c;
        left = nullptr;
        right = nullptr;
    }
};

class MinHeap
{
  private:
    // Increased size to 128 to handle punctuation/spaces safely
    Node *arr[128];
    int capacity;
    int curr;

  public:
    MinHeap()
    {
        capacity = 128;
        curr = 0;
        for (int i = 0; i < capacity; i++)
        {
            arr[i] = nullptr;
        }
    }

    int getSize()
    {
        return curr;
    }

    Node *getRoot()
    {
        if (curr > 0)
            return arr[0];
        return nullptr;
    }

    void insert(Node *data)
    {
        if (curr < capacity)
        {
            arr[curr] = data;
            heapifyUp(curr);
            curr++;
        }
    }

    int leftChild(int i)
    {
        if ((i * 2 + 1) < curr)
            return i * 2 + 1;
        return -1;
    }

    int rightChild(int i)
    {
        if ((i * 2 + 2) < curr)
            return i * 2 + 2;
        return -1;
    }

    int parent(int i)
    {
        if (i > 0)
            return (i - 1) / 2;
        return -1;
    }

    int min(int x, int y)
    {
        if (arr[x]->count < arr[y]->count)
            return x;
        return y;
    }

    Node *deleteData()
    {
        if (curr == 0)
            return nullptr;
        Node *temp = arr[0];
        arr[0] = arr[curr - 1];
        curr--;
        heapifyDown(0);
        return temp;
    }

    void heapifyDown(int i)
    {
        while (i < curr)
        {
            int leftIndex = leftChild(i);
            int rightIndex = rightChild(i);
            int smallest = i;

            if (leftIndex != -1 && arr[leftIndex]->count < arr[smallest]->count)
                smallest = leftIndex;

            if (rightIndex != -1 && arr[rightIndex]->count < arr[smallest]->count)
                smallest = rightIndex;

            if (smallest != i)
            {
                swap(arr[smallest], arr[i]);
                i = smallest;
            }
            else
            {
                break;
            }
        }
    }

    void heapifyUp(int i)
    {
        while (i > 0)
        {
            int parentIndex = parent(i);
            if (parentIndex != -1 && arr[i]->count < arr[parentIndex]->count)
            {
                swap(arr[i], arr[parentIndex]);
                i = parentIndex;
            }
            else
            {
                break;
            }
        }
    }

    void print()
    {
        if (!curr)
            return;
        cout << "\nHeap Contents: ";
        for (int i = 0; i < curr; i++)
        {
            cout << "['" << arr[i]->data << "':" << arr[i]->count << "] ";
        }
        cout << endl;
    }

    ~MinHeap()
    {
    }
};

// Simplified LinkedList for Char storage
template <typename T> class LinkedList
{
  private:
    class Node
    {
      public:
        LinkedList::Node *next;
        T data;
        int count;

        Node(T d)
        {
            next = nullptr;
            data = d;
            count = 1;
        }
    };
    LinkedList::Node *head;
    LinkedList::Node *tail;

  public:
    LinkedList::Node *getHead()
    {
        return head;
    }

    LinkedList()
    {
        head = tail = nullptr;
    }

    void Insert(T d)
    {
        Node *n = Search(d);
        if (!n)
        {
            Node *newNode = new Node(d);
            if (!head)
            {
                head = tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
        else
        {
            n->count++;
        }
    }

    Node *Search(T val)
    {
        Node *move = head;
        while (move)
        {
            if (move->data == val)
                return move;
            move = move->next;
        }
        return nullptr;
    }

    void Display()
    {
        Node *temp = head;
        cout << "Frequencies: ";
        while (temp)
        {
            cout << "['" << temp->data << "':" << temp->count << "] ";
            temp = temp->next;
        }
        cout << endl;
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

int readFile(string fileName, LinkedList<char> &lst)
{
    int count = 0;
    ifstream file(fileName);
    if (!file)
    {
        // Fallback for demo if file doesn't exist
        string demo = "this is a data structure class";
        for (char c : demo)
        {
            lst.Insert(c);
            count++;
        }
        return count;
    }

    char c;
    while (file.get(c))
    {
        if (c != '\n' && c != '\r')
        { // optional: ignore newlines to keep it clean
            lst.Insert(c);
            count++;
        }
    }
    file.close();
    return count;
}

void listToHeap(LinkedList<char> &lst, MinHeap &mnH)
{
    auto node = lst.getHead();
    while (node)
    {
        Node *temp = new Node(node->data, node->count);
        mnH.insert(temp);
        node = node->next;
    }
}

// ---------------------------------------------------------
// QUESTION 1: Fixed Length Encoding (FLE)
// ---------------------------------------------------------
void calculateFixedLengthEncoding(int totalChars, int uniqueChars)
{
    // Calculate bits needed per character: log2(uniqueChars) rounded up
    int bitsPerChar = 0;
    if (uniqueChars > 0)
    {
        // Simple way to do ceil(log2(n)) without math library
        int p = 1;
        while (p < uniqueChars)
        {
            p *= 2;
            bitsPerChar++;
        }
    }

    int totalBits = totalChars * bitsPerChar;

    cout << "1. Fixed Length Encoding (FLE):" << endl;
    cout << "   - Unique Characters: " << uniqueChars << endl;
    cout << "   - Bits per character: " << bitsPerChar << endl;
    cout << "   - Total Size: " << totalBits << " bits" << endl;
}

// Helper to traverse tree and sum up bits
int getHuffmanBits(Node *root, int depth)
{
    if (!root)
        return 0;

    // If leaf node, calculation is count * depth
    if (!root->left && !root->right)
    {
        return root->count * depth;
    }

    // Recursive call for internal nodes
    return getHuffmanBits(root->left, depth + 1) + getHuffmanBits(root->right, depth + 1);
}

// ---------------------------------------------------------
// QUESTION 2: Huffman Encoding Logic
// ---------------------------------------------------------
void performHuffmanEncoding(MinHeap &mnH)
{
    // Build the tree
    // Keep popping 2 nodes until only 1 remains
    while (mnH.getSize() > 1)
    {
        Node *left = mnH.deleteData();
        Node *right = mnH.deleteData();

        // Create a new internal node
        // Data is '\0' (internal marker), Count is sum of children
        Node *top = new Node('\0', left->count + right->count);

        top->left = left;
        top->right = right;

        mnH.insert(top);
    }

    // The remaining node is the root
    Node *root = mnH.getRoot();

    // Calculate size
    int totalBits = getHuffmanBits(root, 0);

    cout << "2. Huffman Encoding:" << endl;
    cout << "   - Total Size: " << totalBits << " bits" << endl;
}

int main()
{
    LinkedList<char> lst;

    // Read file
    int totalChars = readFile("input.txt", lst);

    if (totalChars == 0 && lst.getSize() == 0)
    {
        cout << "No data to process." << endl;
        return 0;
    }

    cout << "Original Size (in bytes/char): " << totalChars * 8 << " bits (" << totalChars << " bytes)" << endl;
    lst.Display();
    cout << "------------------------------------------" << endl;

    // 1. FLE Calculation
    calculateFixedLengthEncoding(totalChars, lst.getSize());

    // Prepare Heap
    MinHeap mnH;
    listToHeap(lst, mnH);

    cout << "------------------------------------------" << endl;

    // 2. Huffman Calculation
    performHuffmanEncoding(mnH);

    return 0;
}