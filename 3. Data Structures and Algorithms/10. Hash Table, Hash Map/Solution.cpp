#include <iostream>
#include <string>
using namespace std;

// Question 1
int simpleHashFunction(string key, int tableSize)
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
    {
        sum += (int)key[i];
    }
    return sum % tableSize;
}

// Question 2
class HashMap
{
  private:
    class Node
    {
      public:
        string key;
        int value;
        Node *next;

        Node(string k, int v)
        {
            key = k;
            value = v;
            next = nullptr;
        }
    };

    Node **table;
    int size;
    int collisionCount;

  public:
    HashMap(int tableSize = 10)
    {
        size = tableSize;
        table = new Node *[size];
        collisionCount = 0;

        for (int i = 0; i < size; i++)
        {
            table[i] = nullptr;
        }
    }

    int hashFunction(string key)
    {
        return simpleHashFunction(key, size);
    }

    void insert(string key, int value)
    {
        int index = hashFunction(key);

        // Check if key already exists
        Node *curr = table[index];
        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // Track collision
        if (table[index] != nullptr)
        {
            collisionCount++;
            cout << "  [Collision detected at index " << index << " for key '" << key << "']" << endl;
        }

        // Insert at head
        Node *newNode = new Node(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    bool search(string key, int &value)
    {
        int index = hashFunction(key);
        Node *curr = table[index];

        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                value = curr->value;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    bool remove(string key)
    {
        int index = hashFunction(key);
        Node *curr = table[index];
        Node *prev = nullptr;

        while (curr != nullptr)
        {
            if (curr->key == key)
            {
                if (prev == nullptr)
                {
                    table[index] = curr->next;
                }
                else
                {
                    prev->next = curr->next;
                }
                delete curr;
                return true;
            }
            prev = curr;
            curr = curr->next;
        }
        return false;
    }

    void display()
    {
        cout << endl << "Hash Table (Chaining) Contents:" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Index " << i << ": ";
            if (table[i] == nullptr)
            {
                cout << "empty";
            }
            else
            {
                Node *curr = table[i];
                while (curr != nullptr)
                {
                    cout << "[" << curr->key << ":" << curr->value << "] -> ";
                    curr = curr->next;
                }
                cout << "NULL";
            }
            cout << endl;
        }
        cout << "Total Collisions: " << collisionCount << endl;
    }

    int getCollisionCount()
    {
        return collisionCount;
    }

    ~HashMap()
    {
        for (int i = 0; i < size; i++)
        {
            Node *curr = table[i];
            while (curr != nullptr)
            {
                Node *temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }
};

// Question 3
class HashTableWithLinearProbing
{
  private:
    class Entry
    {
      public:
        string key;
        int value;
        bool isOccupied;
        bool isDeleted;
    };

    Entry *table;
    int size;
    int collisionCount;

  public:
    HashTableWithLinearProbing(int tableSize = 10)
    {
        size = tableSize;
        table = new Entry[size];
        collisionCount = 0;

        for (int i = 0; i < size; i++)
        {
            table[i].isOccupied = false;
            table[i].isDeleted = false;
        }
    }

    int hashFunction(string key)
    {
        return simpleHashFunction(key, size);
    }

    void insert(string key, int value)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].isOccupied && !table[index].isDeleted)
        {
            if (table[index].key == key)
            {
                table[index].value = value;
                return;
            }

            if (probeCount == 0)
            {
                collisionCount++;
                cout << "  [Collision at index " << index << " for '" << key << "', probing...]" << endl;
            }

            probeCount++;
            index = (originalIndex + probeCount) % size;

            if (probeCount >= size)
            {
                cout << "  [Table full! Cannot insert \'" << key << "\']" << endl;
                return;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
    }

    bool search(string key, int &value)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].isOccupied || table[index].isDeleted)
        {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key)
            {
                value = table[index].value;
                return true;
            }

            probeCount++;
            index = (originalIndex + probeCount) % size;

            if (probeCount >= size)
            {
                break;
            }
        }
        return false;
    }

    bool remove(string key)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].isOccupied || table[index].isDeleted)
        {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key)
            {
                table[index].isDeleted = true;
                return true;
            }

            probeCount++;
            index = (originalIndex + probeCount) % size;

            if (probeCount >= size)
            {
                break;
            }
        }
        return false;
    }

    void display()
    {
        cout << "\nHash Table (Linear Probing) Contents:" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Index " << i << ": ";
            if (!table[i].isOccupied)
            {
                cout << "empty";
            }
            else if (table[i].isDeleted)
            {
                cout << "[DELETED]";
            }
            else
            {
                cout << "[" << table[i].key << ":" << table[i].value << "]";
            }
            cout << endl;
        }
        cout << "Total Collisions: " << collisionCount << endl;
    }

    int getCollisionCount()
    {
        return collisionCount;
    }

    ~HashTableWithLinearProbing()
    {
        delete[] table;
    }
};

// Question 3: Quadratic Probing
class HashTableWithQuadraticProbing
{
  private:
    struct Entry
    {
        string key;
        int value;
        bool isOccupied;
        bool isDeleted;
    };

    Entry *table;
    int size;
    int collisionCount;

  public:
    HashTableWithQuadraticProbing(int tableSize = 10)
    {
        size = tableSize;
        table = new Entry[size];
        collisionCount = 0;

        for (int i = 0; i < size; i++)
        {
            table[i].isOccupied = false;
            table[i].isDeleted = false;
        }
    }

    int hashFunction(string key)
    {
        return simpleHashFunction(key, size);
    }

    void insert(string key, int value)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].isOccupied && !table[index].isDeleted)
        {
            if (table[index].key == key)
            {
                table[index].value = value;
                return;
            }

            if (probeCount == 0)
            {
                collisionCount++;
                cout << "  [Collision at index " << index << " for '" << key << "', quadratic probing...]" << endl;
            }

            probeCount++;
            index = (originalIndex + probeCount * probeCount) % size;

            if (probeCount >= size)
            {
                cout << "  [Table full! Cannot insert '" << key << "']" << endl;
                return;
            }
        }

        table[index].key = key;
        table[index].value = value;
        table[index].isOccupied = true;
        table[index].isDeleted = false;
    }

    bool search(string key, int &value)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].isOccupied || table[index].isDeleted)
        {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key)
            {
                value = table[index].value;
                return true;
            }

            probeCount++;
            index = (originalIndex + probeCount * probeCount) % size;

            if (probeCount >= size)
            {
                break;
            }
        }
        return false;
    }

    bool remove(string key)
    {
        int index = hashFunction(key);
        int originalIndex = index;
        int probeCount = 0;

        while (table[index].isOccupied || table[index].isDeleted)
        {
            if (table[index].isOccupied && !table[index].isDeleted && table[index].key == key)
            {
                table[index].isDeleted = true;
                return true;
            }

            probeCount++;
            index = (originalIndex + probeCount * probeCount) % size;

            if (probeCount >= size)
            {
                break;
            }
        }
        return false;
    }

    void display()
    {
        cout << "\nHash Table (Quadratic Probing) Contents:" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Index " << i << ": ";
            if (!table[i].isOccupied)
            {
                cout << "empty";
            }
            else if (table[i].isDeleted)
            {
                cout << "[DELETED]";
            }
            else
            {
                cout << "[" << table[i].key << ":" << table[i].value << "]";
            }
            cout << endl;
        }
        cout << "Total Collisions: " << collisionCount << endl;
    }

    int getCollisionCount()
    {
        return collisionCount;
    }

    ~HashTableWithQuadraticProbing()
    {
        delete[] table;
    }
};

int main()
{
    // Test data
    string names[] = {"Asjad", "Raza", "Ali", "Rehan", "Ahmad", "Muhammad", "Moosa", "Farhan", "Shaheer"};

    // Additional names with same ASCII sum for collision testing
    string collisionNames[] = {"abc", "bca", "cab"};

    int numNames = 9;
    int numCollisionNames = 3;

    cout << endl << "======= Question 1: Simple Hash Function =======" << endl;

    cout << "Hash Function: hash(string) = (sum of ASCII values) % 10 " << endl;

    for (int i = 0; i < numNames; i++)
    {
        int hashValue = simpleHashFunction(names[i], 10);
        cout << "Key: '" << names[i] << "' => Hash Value: " << hashValue << endl;
    }

    cout << endl << "Testing collision names (same ASCII sum):" << endl;
    for (int i = 0; i < numCollisionNames; i++)
    {
        int hashValue = simpleHashFunction(collisionNames[i], 10);
        cout << "Key: '" << collisionNames[i] << "' => Hash Value: " << hashValue << endl;
    }

    cout << endl << endl << "======= Question 2: Hash Table with Chaining =======" << endl;

    HashMap hashMap;

    cout << "Inserting elements..." << endl;
    for (int i = 0; i < numNames; i++)
    {
        hashMap.insert(names[i], (i + 1) * 100);
        cout << "Inserted: '" << names[i] << "' with value " << (i + 1) * 100 << endl;
    }

    cout << "\nInserting collision test names..." << endl;
    for (int i = 0; i < numCollisionNames; i++)
    {
        hashMap.insert(collisionNames[i], (i + 1) * 10);
        cout << "Inserted: '" << collisionNames[i] << "' with value " << (i + 1) * 10 << endl;
    }

    hashMap.display();

    cout << endl << "--- Testing Search Operation ---" << endl;
    int value;
    if (hashMap.search("Ali", value))
    {
        cout << "Found 'Ali' with value: " << value << endl;
    }
    if (hashMap.search("Shaheer", value))
    {
        cout << "Found 'Shaheer' with value: " << value << endl;
    }
    if (!hashMap.search("NotExist", value))
    {
        cout << "'NotExist' not found in hash table" << endl;
    }

    cout << endl << "--- Testing Delete Operation ---" << endl;
    if (hashMap.remove("Raza"))
    {
        cout << "Successfully deleted 'Raza'" << endl;
    }
    if (!hashMap.remove("NotExist"))
    {
        cout << "Failed to delete 'NotExist' (not found)" << endl;
    }

    hashMap.display();

    cout << endl << endl << "======= Question 3a: Hash Table with Linear Probing =======" << endl;

    HashTableWithLinearProbing linearTable;

    cout << "Inserting elements..." << endl;
    for (int i = 0; i < numNames; i++)
    {
        linearTable.insert(names[i], (i + 1) * 100);
        cout << "Inserted: '" << names[i] << "' with value " << (i + 1) * 100 << endl;
    }

    cout << endl << "Inserting collision test names..." << endl;
    for (int i = 0; i < numCollisionNames; i++)
    {
        linearTable.insert(collisionNames[i], (i + 1) * 10);
        cout << "Inserted: '" << collisionNames[i] << "' with value " << (i + 1) * 10 << endl;
    }

    linearTable.display();

    cout << endl << "--- Testing Search Operation ---" << endl;
    if (linearTable.search("Ali", value))
    {
        cout << "Found 'Ali' with value: " << value << endl;
    }
    if (linearTable.search("Moosa", value))
    {
        cout << "Found 'Moosa' with value: " << value << endl;
    }

    cout << endl << "--- Testing Delete Operation ---" << endl;
    if (linearTable.remove("Ahmad"))
    {
        cout << "Successfully deleted 'Ahmad'" << endl;
    }

    linearTable.display();

    cout << endl << endl << "======= Question 3b: Hash Table with Quadratic Probing =======" << endl;

    HashTableWithQuadraticProbing quadraticTable;

    cout << "Inserting elements..." << endl;
    for (int i = 0; i < numNames; i++)
    {
        quadraticTable.insert(names[i], (i + 1) * 100);
        cout << "Inserted: '" << names[i] << "' with value " << (i + 1) * 100 << endl;
    }

    cout << endl << "Inserting collision test names..." << endl;
    for (int i = 0; i < numCollisionNames; i++)
    {
        quadraticTable.insert(collisionNames[i], (i + 1) * 10);
        cout << "Inserted: '" << collisionNames[i] << "' with value " << (i + 1) * 10 << endl;
    }

    quadraticTable.display();

    cout << endl << "--- Testing Search Operation ---" << endl;
    if (quadraticTable.search("Muhammad", value))
    {
        cout << "Found 'Muhammad' with value: " << value << endl;
    }

    cout << endl << "--- Testing Delete Operation ---" << endl;
    if (quadraticTable.remove("Farhan"))
    {
        cout << "Successfully deleted 'Farhan'" << endl;
    }

    quadraticTable.display();

    cout << endl << endl << "======= Question 4: Performance Evaluation =======" << endl;

    // Performance comparison
    cout << endl << endl << "--- Performance Comparison ---" << endl << endl;
    cout << endl << "--- Analysis ---" << endl;
    cout << "1. Chaining handles collisions by maintaining linked lists." << endl;
    cout << "2. Linear probing finds next available slot sequentially." << endl;
    cout << "3. Quadratic probing reduces clustering compared to linear probing." << endl;
    cout << "4. Performance depends on load factor and hash function quality." << endl;

    cout << endl;

    return 0;
}