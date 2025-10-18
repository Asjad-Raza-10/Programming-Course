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
        Node(K k, V v) : key(k), value(v), left(nullptr), right(nullptr)
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

    Node *remove(Node *node, K key, bool &r)
    {
        if (!node)
        {
            return node;
        }
        if (key < node->key)
        {
            node->left = remove(node->left, key, r);
        }
        else if (key > node->key)
        {
            node->right = remove(node->right, key, r);
        }
        else
        {
            r = true;
            if (!node->left)
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right)
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                Node *temp = findMax(node->left);
                node->key = temp->key;
                node->value = temp->value;
                node->left = remove(node->left, temp->key, r);
            }
        }
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

  public:
    SpecialBST() : root(nullptr)
    {
    }

    bool insert(K k, V v)
    {
        if (!root)
        {
            root = new Node(k, v);
            return true;
        }
        else
        {
            Node *temp = root;
            while (true)
            {
                if (temp->key < k)
                {
                    if (!temp->right)
                    {
                        temp->right = new Node(k, v);
                        return true;
                    }
                    temp = temp->right;
                }
                else if (temp->key > k)
                {
                    if (!temp->left)
                    {
                        temp->left = new Node(k, v);
                        return true;
                    }
                    temp = temp->left;
                }
                else
                {
                    return false;
                }
            }
        }
    }

    V *search(K k)
    {
        if (!root)
        {
            return nullptr;
        }
        if (root->key == k)
        {
            return &root->value;
        }

        Node *temp = root;
        while (true)
        {
            if (temp->key < k)
            {
                if (!temp->right)
                {
                    return nullptr;
                }
                temp = temp->right;
            }
            else if (temp->key > k)
            {
                if (!temp->left)
                {
                    return nullptr;
                }
                temp = temp->left;
            }
            else
            {
                return &temp->value;
            }
        }
    }

    bool remove(K key)
    {
        bool removed = false;
        root = remove(root, key, removed);
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
        if (root->key == k)
        {
            return root;
        }

        Node *temp = root;
        while (true)
        {
            if (temp->key < k)
            {
                if (!temp->right)
                {
                    return nullptr;
                }
                temp = temp->right;
            }
            else if (temp->key > k)
            {
                if (!temp->left)
                {
                    return nullptr;
                }
                temp = temp->left;
            }
            else
            {
                return &temp;
            }
        }
    }

    bool update(K oldKey, K newKey, V newValue)
    {
        if (search(oldKey))
        {
            bool f = 0; // just to pass in the function
            root = remove(root, oldKey, f);
            if (insert(newKey, newValue))
            {
                cout << "\nRecord updated inserted successfully!\n";
                return true;
            }
            else
            {
                cout << "\nRoll Number already exists!\n";
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

        for (int i = 0; i < s.capacity(); i++)
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

        default: {
            cout << "\nInvalid choice! Please try again.\n";
            break;
        }
        }

    } while (choice != 'E' && choice != 'e');

    return 0;
}