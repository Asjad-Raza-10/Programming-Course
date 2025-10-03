#include <fstream>
#include <iostream>
#include <string>

using namespace std;

template <typename T> class Stack
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

    Node *front;
    Node *rear;

  public:
    Stack()
    {
        front = rear = nullptr;
    }

    Stack(T num)
    {
        Node *n = new Node(num);
        front = rear = n;
    }

    void push(T d)
    {
        Node *n = new Node(d);
        if (!front)
        {
            front = rear = n;
            return;
        }

        rear->next = n;
        rear = n;
    }

    T pop()
    {
        if (!front)
        {
            return T();
        }

        T temp = rear->data;

        if (front == rear)
        {
            delete front;
            front = rear = nullptr;
            return temp;
        }

        Node *move = front;
        Node *prev = nullptr;

        while (move)
        {
            if (!move->next)
            {
                delete rear;
                rear = prev;
                rear->next = nullptr;
                break;
            }

            prev = move;
            move = move->next;
        }

        return temp;
    }

    void print()
    {
        cout << endl << "Stack with Linked List is: ";
        Node *temp = front;

        cout << temp->data;
        temp = temp->next;

        while (temp)
        {
            cout << " <- " << temp->data;

            temp = temp->next;
        }

        cout << endl << endl;
    }

    bool isEmpty()
    {
        return !front;
    }

    T peek()
    {
        return rear->data;
    }

    ~Stack()
    {
        while (front)
        {
            Node *move = front;
            front = front->next;
            delete move;
        }
    }
};

int main()
{
    Stack<string> tags;
    bool allGood = true;

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
        allGood = false;
    }

    if (i >= line.size() || line[i++] != '?')
    {
        cerr << "Error: Header not defined" << endl;
        allGood = false;
    }

    i = line.size() - 1;
    if (line[i] != '>')
    {
        cerr << "Error: No closing tag for the header" << endl;
        allGood = false;
    }

    if (i == 0 || line[i - 1] != '?')
    {
        cerr << "Error: No closing ? for the header" << endl;
        allGood = false;
    }

    // inner string checks
    while (getline(file, line))
    {
        bool openingBracketFound = false;
        bool closingTagFound = false;
        bool attributeFound = false;
        bool firstCommaFound = false;
        bool commentStartFound = false;
        bool commentCompleted = false;
        char commaUsed = '\0';
        string tag = "";

        for (int i = 0; i < line.length(); i++)
        {
            char c = line[i];

            if (c == '-') // ending of comment
            {
                if (commentStartFound)
                {
                    if (line[i + 1] == '-' && line[i + 2] == '>')
                    {
                        commentStartFound = false;
                        commentCompleted = true;
                    }
                    else
                    {
                        cerr << "Invalid closing for comment." << endl;
                        allGood = false;
                    }
                }
            }
            else if (c == '<')
            {
                if (openingBracketFound)
                {
                    cerr << "Multiple Tags opened before closing the previous one." << endl;
                    allGood = false;
                }
                else
                {
                    openingBracketFound = true;
                }

                if (line[i + 1] == '!')
                {
                    if (line[i + 2] == '-' && line[i + 3] == '-')
                    {
                        commentStartFound = true;
                    }
                    else
                    {
                        cerr << "Error: Invalid starting for comment." << endl;
                        allGood = false;
                    }
                }
            }
            else if (c == '>')
            {
                if (commentCompleted)
                {
                    commentCompleted = false;
                    continue;
                }
                if (attributeFound || firstCommaFound)
                {
                    cerr << "Error: Inverted comma for value was not closed before ending tag." << endl;
                    allGood = false;
                }
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
                                allGood = false;
                            }
                            else
                            {
                                string getTag = tags.pop();
                                if (tag != getTag)
                                {
                                    cerr << getTag << " was opened but a different tag i.e. " << tag
                                         << " is being closed before the opened one." << endl;
                                    allGood = false;
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
                    allGood = false;
                }
            }
            else if (openingBracketFound)
            {
                if (c == '/')
                {
                    closingTagFound = true;
                }
                if (c == '=')
                {
                    attributeFound = true;
                }
                else
                {
                    tag += c;
                }
            }
            else if (attributeFound)
            {
                if (!firstCommaFound)
                {
                    if (c != 34 && c != 39) // ASCII for ' and ""
                    {
                        cerr << "Error: No commas used for attribute value." << endl;
                        allGood = false;
                    }
                    else
                    {
                        commaUsed = c;
                        firstCommaFound = true;
                    }
                }
                else
                {
                    if (c == 34 || c == 39)
                    {
                        if (c != commaUsed)
                        {
                            cerr << "Error: Different invertrd commas used for defining value." << endl;
                            allGood = false;
                        }
                        attributeFound = false;
                        firstCommaFound = false;
                    }
                }
            }
        }

        lineNumber++;
        cout << endl << "Line " << lineNumber << ": " << line << endl;
    }

    // if any tags were not closed
    while (!tags.isEmpty())
    {
        string unclosedTag = tags.pop();
        cerr << "Error: Closing tag for '" << unclosedTag << "' is missing" << endl;
        allGood = false;
    }

    if (allGood)
    {
        cout << endl << "All Good. No errors in the code." << endl;
    }

    file.close();
    return 0;
}