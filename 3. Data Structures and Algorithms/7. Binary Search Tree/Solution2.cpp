#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

template <typename K, typename V> class SpecialBST
{
  private:
    class Node
    {
      public:
        K key;
        V value;
        Node *left;
        Node *right;
        Node *parent;
        int height;

        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr), parent(nullptr), height(1)
        {
        }
    };

    Node *root;

    // helping functions recursion
    Node *findMax(Node *node)
    {
        if (!node)
        {
            return node;
        }
        while (node && node->right)
        {
            node = node->right;
        }
        return node;
    }

    Node *remove(Node *node, K key, bool &r, Node *&parentOfDeleted)
    {
        if (!node)
        {
            return node;
        }

        if (key < node->key)
        {
            node->left = remove(node->left, key, r, parentOfDeleted);
            if (node->left)
            {
                node->left->parent = node;
            }
        }
        else if (key > node->key)
        {
            node->right = remove(node->right, key, r, parentOfDeleted);
            if (node->right)
            {
                node->right->parent = node;
            }
        }
        else
        {
            r = true;
            parentOfDeleted = node->parent;

            if (!node->left)
            {
                Node *temp = node->right;
                if (temp)
                {
                    temp->parent = node->parent;
                }

                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node *temp = node->left;
                if (temp)
                {
                    temp->parent = node->parent;
                }

                delete node;
                return temp;
            }
            else
            {
                Node *temp = findMax(node->left);
                node->key = temp->key;
                node->value = temp->value;
                node->left = remove(node->left, temp->key, r, parentOfDeleted);
                if (node->left)
                {
                    node->left->parent = node;
                }

                parentOfDeleted = node;
            }
        }

        node->height = max(Height(node->left), Height(node->right)) + 1;
        return node;
    }

    void clear(Node *node)
    {
        if (!node)
        {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
        node = nullptr;
    }

    void inOrder(Node *node, vector<V> &vect)
    {
        if (!node)
        {
            return;
        }
        inOrder(node->left, vect);
        vect.push_back(node->value);
        inOrder(node->right, vect);
    }

    void inOrderWithKeys(Node *node, vector<K> &keys, vector<V> &values)
    {
        if (!node)
        {
            return;
        }
        inOrderWithKeys(node->left, keys, values);
        values.push_back(node->value);
        keys.push_back(node->key);
        inOrderWithKeys(node->right, keys, values);
    }

    // Functions for rotation till root

    int Height(Node *temp)
    {
        if (!temp)
        {
            return 0;
        }
        return temp->height;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node *rightRotation(Node *x)
    {
        Node *y = x->left;
        Node *T2 = y->right;

        // Perform rotation
        y->right = x;
        x->left = T2;

        // Update parent pointers
        y->parent = x->parent;
        x->parent = y;
        if (T2)
        {
            T2->parent = x;
        }

        // Update heights
        x->height = max(Height(x->left), Height(x->right)) + 1;
        y->height = max(Height(y->left), Height(y->right)) + 1;

        return y;
    }

    Node *leftRotation(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update parent pointers
        y->parent = x->parent;
        x->parent = y;
        if (T2)
        {
            T2->parent = x;
        }

        // Update heights
        x->height = max(Height(x->left), Height(x->right)) + 1;
        y->height = max(Height(y->left), Height(y->right)) + 1;

        return y;
    }

    int getBalanceFactor(Node *temp)
    {
        if (!temp)
        {
            return 0;
        }
        return Height(temp->left) - Height(temp->right);
    }

    void moveToRoot(Node *node)
    {
        if (node == nullptr)
            return;

        while (node != root) // Keep rotating until node becomes root
        {
            Node *parent = node->parent;

            if (!parent) // Already root
            {
                break;
            }

            Node *grandparent = parent->parent;

            if (!grandparent) // Parent is root (single rotation)
            {
                if (node == parent->left)
                {
                    root = rightRotation(parent);
                }
                else
                {
                    root = leftRotation(parent);
                }
            }
            else // Has grandparent (double rotation)
            {
                Node *greatGrandparent = grandparent->parent;
                bool isLeftChild = (greatGrandparent != nullptr && grandparent == greatGrandparent->left);

                if (node == parent->left && parent == grandparent->left) // Left-Left
                {
                    Node *newSubtreeRoot = rightRotation(grandparent);
                    newSubtreeRoot = rightRotation(newSubtreeRoot);

                    if (greatGrandparent)
                    {
                        if (isLeftChild)
                        {
                            greatGrandparent->left = newSubtreeRoot;
                        }
                        else
                        {
                            greatGrandparent->right = newSubtreeRoot;
                        }
                        newSubtreeRoot->parent = greatGrandparent;
                    }
                    else
                    {
                        root = newSubtreeRoot;
                        root->parent = nullptr;
                    }
                }
                else if (node == parent->right && parent == grandparent->right) // Right-Right
                {
                    Node *newSubtreeRoot = leftRotation(grandparent);
                    newSubtreeRoot = leftRotation(newSubtreeRoot);

                    if (greatGrandparent)
                    {
                        if (isLeftChild)
                        {
                            greatGrandparent->left = newSubtreeRoot;
                        }
                        else
                        {
                            greatGrandparent->right = newSubtreeRoot;
                        }
                        newSubtreeRoot->parent = greatGrandparent;
                    }
                    else
                    {
                        root = newSubtreeRoot;
                        root->parent = nullptr;
                    }
                }
                else if (node == parent->right && parent == grandparent->left) // Left-Right
                {
                    Node *newSubtreeRoot = leftRotation(parent);
                    grandparent->left = newSubtreeRoot;
                    newSubtreeRoot->parent = grandparent;

                    newSubtreeRoot = rightRotation(grandparent);

                    if (greatGrandparent != nullptr)
                    {
                        if (isLeftChild)
                        {
                            greatGrandparent->left = newSubtreeRoot;
                        }
                        else
                        {
                            greatGrandparent->right = newSubtreeRoot;
                        }
                        newSubtreeRoot->parent = greatGrandparent;
                    }
                    else
                    {
                        root = newSubtreeRoot;
                        root->parent = nullptr;
                    }
                }
                else // Right-Left
                {
                    Node *newSubtreeRoot = rightRotation(parent);
                    grandparent->right = newSubtreeRoot;
                    newSubtreeRoot->parent = grandparent;

                    newSubtreeRoot = leftRotation(grandparent);

                    if (greatGrandparent)
                    {
                        if (isLeftChild)
                        {
                            greatGrandparent->left = newSubtreeRoot;
                        }
                        else
                        {
                            greatGrandparent->right = newSubtreeRoot;
                        }
                        newSubtreeRoot->parent = greatGrandparent;
                    }
                    else
                    {
                        root = newSubtreeRoot;
                        root->parent = nullptr;
                    }
                }
            }
        }
    }

  public:
    SpecialBST() : root(nullptr)
    {
    }

    bool insert(K k, V v)
    {
        if (!root)
        {
            root = new Node(k, v);
            // No need to move to root, already at root
            return true;
        }
        else
        {
            Node *temp = root;
            Node *newNode = nullptr;

            while (true)
            {
                if (temp->key < k)
                {
                    if (!temp->right)
                    {
                        temp->right = new Node(k, v);
                        temp->right->parent = temp; // Set parent
                        newNode = temp->right;      // Save pointer
                        break;
                    }
                    temp = temp->right;
                }
                else if (temp->key > k)
                {
                    if (!temp->left)
                    {
                        temp->left = new Node(k, v);
                        temp->left->parent = temp; // Set parent
                        newNode = temp->left;      // Save pointer
                        break;
                    }
                    temp = temp->left;
                }
                else
                {
                    // Duplicate key found, move it to root
                    moveToRoot(temp);
                    return false;
                }
            }

            // Move the newly inserted node to root
            moveToRoot(newNode);
            return true;
        }
    }

    V *search(K k)
    {
        if (!root)
        {
            return nullptr;
        }

        Node *temp = root;
        Node *lastAccessed = root; // Track last accessed node

        while (temp)
        {
            lastAccessed = temp; // Update last accessed

            if (temp->key == k)
            {
                // Move the found node to root
                moveToRoot(temp);
                return &temp->value;
            }
            else if (temp->key < k)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        // Not found, move the last accessed node (where search terminated) to root
        moveToRoot(lastAccessed);
        return nullptr;
    }

    bool remove(K key)
    {
        bool removed = false;
        Node *parentOfDeleted = nullptr;

        root = remove(root, key, removed, parentOfDeleted);

        if (root)
        {
            root->parent = nullptr; // Root has no parent
        }

        if (removed && parentOfDeleted)
        {
            // Move the parent of deleted node to root
            moveToRoot(parentOfDeleted);
        }
        else if (!removed)
        {
            // Key not found, find and move last accessed node to root
            Node *temp = root;
            Node *lastAccessed = root;

            while (temp)
            {
                lastAccessed = temp;

                if (temp->key == key)
                {
                    break;
                }
                else if (temp->key < key)
                {
                    temp = temp->right;
                }
                else
                {
                    temp = temp->left;
                }
            }

            if (lastAccessed)
            {
                moveToRoot(lastAccessed);
            }
        }

        return removed;
    }

    vector<V> getValuesinOrder()
    {
        vector<V> vect;

        if (!root)
        {
            return vect;
        }

        inOrder(root, vect);
        return vect;
    }

    vector<V> getValuesLevelWise()
    {
        vector<V> vect;

        if (!root)
        {
            return vect;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            Node *temp = q.front();
            q.pop();

            vect.push_back(temp->value);

            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            }
        }

        return vect;
    }

    Node *searchNode(K k)
    {
        if (!root)
        {
            return nullptr;
        }

        Node *temp = root;
        Node *lastAccessed = root;

        while (temp)
        {
            lastAccessed = temp;

            if (temp->key == k)
            {
                // Move the found node to root
                moveToRoot(temp);
                return temp;
            }
            else if (temp->key < k)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        // Not found, move the last accessed node to root
        moveToRoot(lastAccessed);
        return nullptr;
    }

    bool update(K oldKey, K newKey, V newValue)
    {
        if (search(oldKey)) // This will move the found node to root
        {
            bool f = false;
            Node *parentOfDeleted = nullptr;
            root = remove(root, oldKey, f, parentOfDeleted);

            if (root)
            {
                root->parent = nullptr;
            }

            if (insert(newKey, newValue)) // This will move the new node to root
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }

    void GetValuesWithKeys(vector<K> &keys, vector<V> &values)
    {
        if (!root)
        {
            return;
        }
        inOrderWithKeys(root, keys, values);
        return;
    }

    bool isEmpty()
    {
        return !root;
    }

    ~SpecialBST()
    {
        clear(root);
        root = nullptr;
    }
};

class StudentList
{
  private:
    class StudentAttributes
    {
      private:
        string firstName;
        string lastName;
        int batch;
        string department;
        float cgpa;

      public:
        StudentAttributes(string f = "", string l = "", int b = 0, string d = "", float c = 0)
        {
            firstName = f;
            lastName = l;
            batch = b;
            department = d;
            cgpa = c;
        }

        void print()
        {
            cout << "First Name: " << firstName << endl;
            cout << "Last Name: " << lastName << endl;
            cout << "Batch: " << batch << endl;
            cout << "Department: " << department << endl;
            cout << "CGPA: " << cgpa << endl;
            cout << "First Name: " << firstName << endl;
        }

        void operator=(const StudentAttributes &other)
        {
            this->firstName = other.firstName;
            this->lastName = other.lastName;
            this->batch = other.batch;
            this->department = other.department;
            this->cgpa = other.cgpa;
        }

        void UpdateAttributes(string f, string l, int b, string d, float c)
        {
            firstName = f;
            lastName = l;
            batch = b;
            department = d;
            cgpa = c;
        }
    };
    // int will have roll number
    SpecialBST<int, StudentAttributes> students;

  public:
    StudentList() : students()
    {
    }

    bool InsertNewStudent(int r, string f, string l, int b, string d, float c)
    {
        StudentAttributes s(f, l, b, d, c);
        return students.insert(r, s);
    }

    bool deleteStudent(int r)
    {
        return students.remove(r);
    }

    bool updateStudent(int oldRollNo, int newRollNo, string f, string l, int b, string d, float c)
    {
        StudentAttributes s(f, l, b, d, c);
        return students.update(oldRollNo, newRollNo, s);
    }

    void searchAndPrintStudent(int rollNo)
    {
        StudentAttributes *s;
        s = students.search(rollNo);
        if (s)
        {
            cout << "Student with roll number " << rollNo << " found." << endl;
            cout << "Details of the student: " << endl;
            s->print();
        }
        else
        {
            cout << "Student with roll number " << rollNo << " does not exist." << endl;
        }
    }

    void printAllStudentsWithoutRollNumbers()
    {
        if (students.isEmpty())
        {
            cout << endl << "Students Record is Empty!" << endl;
            return;
        }

        vector<StudentAttributes> s = students.getValuesinOrder();

        cout << endl << "======== STUDENTS RECORD =======" << endl;

        for (auto i : s)
        {
            i.print();
            cout << endl << "------------" << endl;
        }

        cout << endl;
    }

    void printAllStudentsWithRollNumbers()
    {
        vector<int> rollNo;
        vector<StudentAttributes> s;

        students.GetValuesWithKeys(rollNo, s);

        cout << endl << "======== STUDENTS RECORD =======" << endl;

        for (int i = 0; i < s.size(); i++)
        {
            cout << "Roll Number: " << rollNo[i] << endl;
            s[i].print();
            cout << "------------" << endl;
        }

        cout << endl;
    }
};

void getFloatInput(float &num)
{
    while (!(cin >> num) || (num < 0))
    {
        cout << "Invalid input. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidCGPA(float cgpa)
{
    if (cgpa < 0.0 || cgpa > 4.0)
    {
        cout << "Invalid CGPA. Please enter a CGPA between 0.0 and 4.0: ";
        return false;
    }
    return true;
}

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

void getName(string &name)
{
    bool valid = false;
    while (!valid)
    {
        getline(cin, name);
        if (name.empty() || name.find_first_not_of(' ') == string::npos)
        {
            cout << "Invalid name! Name cannot be empty." << endl;
            cout << "Please input the name again: ";
            valid = false;
            continue;
        }
        valid = true;
        for (char c : name)
        {
            if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' '))
            {
                cout << "Invalid name! Only alphabets and spaces are allowed." << endl;
                cout << "Please input the name again: ";
                valid = false;
                break;
            }
        }
    }
}

bool isValidYear(int year)
{
    if (year < 1 || year > 2025)
    {
        cout << "Invalid year. Please enter a year between 1 and 2025: ";
        return false;
    }
    return true;
}

void testSpecialBST()
{
    SpecialBST<int, int> bst;

    cout << "======= Testing SpecialBST with moveToRoot =======\n\n";

    // Insert values
    cout << "Inserting: 50, 30, 70, 20, 40, 60\n\n";

    bst.insert(50, 50);
    cout << "After inserting 50 (should be root):\n";
    cout << "Level-wise: ";
    vector<int> v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    bst.insert(30, 30);
    cout << "After inserting 30 (30 moves to root):\n";
    cout << "Level-wise: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    bst.insert(70, 70);
    cout << "After inserting 70 (70 moves to root):\n";
    cout << "Level-wise: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    bst.insert(20, 20);
    cout << "After inserting 20 (20 moves to root):\n";
    cout << "Level-wise: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    bst.insert(40, 40);
    cout << "After inserting 40 (40 moves to root):\n";
    cout << "Level-wise: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    bst.insert(60, 60);
    cout << "After inserting 60 (60 moves to root):\n";
    cout << "Level-wise: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    // Test search
    cout << "Searching for 20 (20 should move to root):\n";
    int *result = bst.search(20);
    if (result)
        cout << "Found: " << *result << endl;
    cout << "Level-wise after search: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    // Test search for non-existent key
    cout << "Searching for 25 (not found, last accessed node moves to root):\n";
    result = bst.search(25);
    if (result)
        cout << "Found: " << *result << endl;
    else
        cout << "Not found!" << endl;
    cout << "Level-wise after failed search: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    // Test delete
    cout << "Deleting 30 (parent of deleted moves to root):\n";
    bool deleted = bst.remove(30);
    cout << (deleted ? "Deleted successfully" : "Not found") << endl;
    cout << "Level-wise after delete: ";
    v = bst.getValuesLevelWise();
    for (int i : v)
        cout << i << " ";
    cout << "\n\n";

    cout << "Final In-order traversal (should be sorted): ";
    vector<int> inorder = bst.getValuesinOrder();
    for (int i : inorder)
        cout << i << " ";
    cout << "\n";
}

int main()
{
    StudentList studentList;
    char choice;

    do
    {
        cout << "\n\t\t======= Student Management System =======\n\n";
        cout << "Press I to insert a new student.\n";
        cout << "Press D to delete a student.\n";
        cout << "Press S to search a student by roll number.\n";
        cout << "Press U to update the data of a student.\n";
        cout << "Press P to print all students sorted by roll number.\n";
        cout << "Press C to check the Special BST Implementation.\n";
        cout << "Press E to exit.\n\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 'I':
        case 'i': {
            int rollNo, batch;
            string firstName, lastName, department;
            float cgpa;

            cout << "\nPlease enter the data of new student:\n";

            cout << "Enter the Roll Number: ";
            getNumInput(rollNo);

            cout << "Enter the First Name: ";
            getName(firstName);

            cout << "Enter the Last Name: ";
            getName(lastName);

            cout << "Enter the Batch: ";
            getNumInput(batch);
            while (!isValidYear(batch))
            {
                getNumInput(batch);
            }

            cout << "Enter the Department: ";
            getline(cin, department);

            cout << "Enter the CGPA: ";
            getFloatInput(cgpa);
            while (!isValidCGPA(cgpa))
            {
                getFloatInput(cgpa);
            }

            if (studentList.InsertNewStudent(rollNo, firstName, lastName, batch, department, cgpa))
            {
                cout << "\nNew student inserted successfully!\n";
            }
            else
            {
                cout << "\nRoll Number already exists!\n";
            }
            break;
        }

        case 'D':
        case 'd': {
            int rollNo;
            cout << "\nPlease enter the roll number of the student that you want to delete: ";
            getNumInput(rollNo);

            if (studentList.deleteStudent(rollNo))
            {
                cout << "\nStudent deleted successfully.\n";
            }
            else
            {
                cout << "\nStudent with this roll number does not exist!\n";
            }
            break;
        }

        case 'S':
        case 's': {
            int rollNo;
            cout << "\nPlease enter the roll number of the student that you want to search: ";
            getNumInput(rollNo);

            studentList.searchAndPrintStudent(rollNo);
            break;
        }

        case 'U':
        case 'u': {
            int oldRollNo, newRollNo, batch;
            string firstName, lastName, department;
            float cgpa;

            cout << "\nPlease enter the roll number of the student whose data you want to update: ";
            getNumInput(oldRollNo);

            cout << "\nPlease enter new data of student:\n";

            cout << "Enter the Roll Number: ";
            getNumInput(newRollNo);

            cout << "Enter the First Name: ";
            getName(firstName);

            cout << "Enter the Last Name: ";
            getName(lastName);

            cout << "Enter the Batch: ";
            getNumInput(batch);
            while (!isValidYear(batch))
            {
                getNumInput(batch);
            }

            cout << "Enter the Department: ";
            getline(cin, department);

            cout << "Enter the CGPA: ";
            getFloatInput(cgpa);
            while (!isValidCGPA(cgpa))
            {
                getFloatInput(cgpa);
            }

            if (studentList.updateStudent(oldRollNo, newRollNo, firstName, lastName, batch, department, cgpa))
            {
                cout << "\nStudent data updated successfully.\n";
            }
            else
            {
                cout << "\nCheck the roll number again!\n";
            }
            break;
        }

        case 'P':
        case 'p': {
            studentList.printAllStudentsWithRollNumbers();
            break;
        }

        case 'E':
        case 'e': {
            cout << "\nExiting the system. Goodbye!\n";
            break;
        }

        case 'c':
        case 'C':
            testSpecialBST();
            break;

        default: {
            cout << "\nInvalid choice! Please try again.\n";
            break;
        }
        }

    } while (choice != 'E' && choice != 'e');

    return 0;
}