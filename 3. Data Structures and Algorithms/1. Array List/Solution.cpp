#include <iostream>
#include <string>

using namespace std;

template <typename T>
class List {
public:
    virtual void insert(T element) = 0;
    virtual void remove(int index) = 0;
    virtual T get(int index) = 0;
    virtual int size() = 0;
    virtual void display() = 0;
    virtual bool isEmpty() = 0;
    virtual bool contains(T element) = 0;
    virtual void clear() = 0;
    virtual bool isFull() = 0;
    virtual bool isHalf() = 0;
    virtual void grow() = 0;
    virtual void shrink() = 0;
    virtual ~List() {}
};

template <typename T>
class ArrayList : public List<T>
{
private:
    int curr_size;
    int capacity;
    T* arr;
public:
    ArrayList()
    {
        curr_size = 0;
        capacity = 10;
        arr = new T[capacity];
    }
    void insert(T element) override
    {
        if (isFull())
        {
            grow();
        }
        arr[curr_size++] = element;
    }

    void remove(int index) override
    {
        if (index < 0 || index > curr_size)
        {
            throw "Error: Invalid Index!";
        }
        cout << endl << "Index " << index << ": " << arr[index].name << " Removed Successfully!" << endl << endl;
        for (int i = index; i < curr_size; i++)
        {
            arr[i] = arr[i + 1];
        }
        curr_size--;

        if (isHalf())
        {
            shrink();
        }
    }

    bool isEmpty() override
    {
        return (curr_size == 0);
    }

    T get(int index) override
    {
        if (index < 0 || index > curr_size)
        {
            throw "Error: Invalid Index!";
        }
        return arr[index];
    }

    bool contains(T element) override
    {
        for (int i = 0; i < curr_size; i++)
        {
            if (arr[i] == element)
            {
                return true;
            }
        }
        return false;
    }

    int size() override
    {
        return curr_size;
    }

    void display() override
    {
        if (curr_size == 0)
        {
            cout << "Array List is empty!";
        }
        else
        {
            for (int i = 0; i < curr_size; i++)
            {
                cout << arr[i] << endl;
            }
        }

    }

    void clear() override
    {
        for (int i = 0; i < curr_size; i++)
        {
            delete[]arr;
            arr = new T[capacity];
        }
        curr_size = 0;
        cout << "The Array List has been cleared." << endl;
    }
    
    bool isFull() override
    {
        return (curr_size == capacity);
    }

    bool isHalf() override
    {
        return (curr_size <= (capacity/2 - 1));
    }

    void grow() override
    {
        capacity *= 2;
        T* temp = new T[capacity];

        for (int i = 0; i < curr_size; i++)
        {
            temp[i] = arr[i];
        }

        delete[]arr;
        arr = temp;
    }

    void shrink() override
    {
        capacity /= 2;
        T* temp = new T[capacity];

        for (int i = 0; i < curr_size; i++)
        {
            temp[i] = arr[i];
        }

        delete[]arr;
        arr = temp;
    }

    ~ArrayList() override
    {
        delete[]arr;
    }
};

class Person {
public:
    string name;
    string gender;
    int age;
    Person(string n = "", string g = "" , int a = 0) 
    {
        name = n;
        gender = g;
        age = a;
    }
    
    friend ostream& operator<<(ostream& os, const Person& p) 
    {
        os << "Name: " << p.name << ", Gender: " << p.gender << ", Age: " << p.age;
        return os;
    }

    bool operator==(const Person&)
    {
        return (this->age == age && this->gender == gender && this->name == name);
    }
};



int main() {
    
    ArrayList<Person> people;

    cout << "Is Array List Empty? " << people.isEmpty() << endl;

    people.insert(Person("Ali", "Male", 20));
    people.insert(Person("Sara", "Female", 22));
    people.insert(Person("Ahmed", "Male", 19));

    cout << endl << "Is Array List Empty? " << people.isEmpty() << endl;

    cout << endl << "All Persons:" << endl;
    people.display();

    cout << "\nRemoving index 1 (Sara)...\n";
    people.remove(1);
    people.display();

    cout << "\nAccessing index 0: " << people.get(0) << endl;

    cout << "\nAccessing index -2: " << endl;
    try
    {
        cout << "Value: " << people.get(-2) << endl;
    }
    catch (const char* e)
    {
        cout << e;
    }

    cout << endl << endl<< "Current Size of Array: " << people.size() << endl;
    people.display();

    cout << endl << "Clearing the Array List." << endl;
    people.clear();
    cout << endl << "Is Array List Empty? " << people.isEmpty() << endl;

    char choice = ' ';
    
    while (1)
    {
        cout << "Input a person Details: " << endl;;
        string name, gender;
        int age;

        cout << "Name: ";  cin >> name;
        cout << "Gender: ";  cin >> gender;
        cout << "Age: ";  cin >> age;

        people.insert(Person(name, gender, age));

        cout << endl << "A record for " << name << " was added." << endl;
        cout << endl << "Press any key to continue adding records." << endl;
        cout << "Press N to stop adding records" << endl << endl;
        cin >> choice;
        if (choice == 'N' || choice == 'n')
        {
            break;
        }
    }
 
    cout << endl << "Current Size of Array List: " << people.size() << endl;
    cout << endl << "All Persons:" << endl;
    people.display();

    return 0;
}
