#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <class T> class Stack
{
    T *arr;
    int capacity;
    int current;

  public:
    Stack(int n = 5)
    {
        capacity = n;
        arr = new T[capacity];
        current = -1;
    }

    bool isEmpty()
    {
        if (current == -1)
            return true;
        return false;
    }

    bool isFull()
    {
        if (current == capacity - 1)
            return true;
        return false;
    }

    void push(T d)
    {
        if (isFull())
        {
            cerr << "Stack is full!" << endl;
        }
        else
        {
            arr[++current] = d;
        }
    }

    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }

        return arr[current--];
    }

    T top()
    {
        if (isEmpty())
        {
            cout << "Stack is empty" << endl;
            return T();
        }
        return arr[current];
    }

    void print()
    {
        for (int i = current; i >= 0; i--)
        {
            cout << arr[i] << endl;
        }
    }

    ~Stack()
    {
        delete[] arr;
    }
};

int main()
{
    Stack<string> tags;

    ifstream file(
        "/Volumes/Data/Portfolio/Github/Programming Course/3. Data Structures and Algorithms/6. Stacks/test.xml");
    if (!file.is_open())
    {
        cout << "Error: Could not open file!" << endl;
        return 1;
    }

    string line;
    int lineNumber = 0;

    getline(file, line);
    int i = 0;

    // header checks
    if (line.size() < 2 || line[i++] != '<')
    {
        cerr << "Error: No opening tag for the header" << endl;
    }

    if (i >= line.size() || line[i++] != '?')
    {
        cerr << "Error: Header not defined" << endl;
    }

    i = line.size() - 1;
    if (line[i] != '>')
    {
        cerr << "Error: No closing tag for the header" << endl;
    }

    if (i == 0 || line[i - 1] != '?')
    {
        cerr << "Error: No closing ? for the header" << endl;
    }

    // inner string checks
    while (getline(file, line))
    {
        bool openingBracketFound = false;
        bool closingTagFound = false;
        string tag = "";
        i = 0;

        while (i < line.size())
        {
            char c = line[i];
            if (c == '<')
            {
                if (openingBracketFound)
                {
                    cerr << "Multiple Tags opened before closing the previous one." << endl;
                }
                else
                {
                    openingBracketFound = true;
                }
            }
            else if (c == '>')
            {
                if (openingBracketFound)
                {
                    openingBracketFound = false;
                    if (!tag.empty())
                    {
                        if (!closingTagFound)
                        {
                            tags.push(tag);
                        }
                        else
                        {
                            if (tags.isEmpty())
                            {
                                cerr << "Error: Closing tag '" << tag << "' without matching opening tag" << endl;
                            }
                            else
                            {
                                string getTag = tags.pop();
                                if (tag != getTag)
                                {
                                    cerr << getTag << " was opened but a different tag i.e. " << tag
                                         << " is being closed before the opened one." << endl;
                                }
                            }
                        }
                    }
                    tag = "";
                    closingTagFound = false;
                }
                else
                {
                    cerr << "Error: Closing Tag doesnot have an opening" << endl;
                }
            }
            else if (openingBracketFound)
            {
                if (c == '/')
                {
                    closingTagFound = true;
                }
                else
                {
                    tag += c;
                }
            }
            i++;
        }

        lineNumber++;
        cout << endl << "Line " << lineNumber << ": " << line << endl;
    }

    // if any tags were not closed
    while (!tags.isEmpty())
    {
        string unclosedTag = tags.pop();
        cerr << "Error: Closing tag for '" << unclosedTag << "' is missing" << endl;
    }

    file.close();
    return 0;
}