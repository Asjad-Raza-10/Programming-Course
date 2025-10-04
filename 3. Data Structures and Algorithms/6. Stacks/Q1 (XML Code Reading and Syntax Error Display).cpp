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
        Node *prev;
        T data;
        int lineNum;

        Node(T d, int line = 0) : prev(nullptr), data(d), lineNum(line)
        {
        }
    };

    Node *top;

  public:
    Stack() : top(nullptr)
    {
    }

    Stack(T num, int line = 0)
    {
        top = new Node(num, line);
    }

    void push(T d, int line = 0)
    {
        Node *n = new Node(d, line);
        n->prev = top;
        top = n;
    }

    T pop()
    {
        if (!top)
            return T();

        T temp = top->data;
        Node *toDelete = top;
        top = top->prev;
        delete toDelete;
        return temp;
    }

    int getLineNum()
    {
        if (!top)
            return 0;
        return top->lineNum;
    }

    void print()
    {
        cout << "\nStack: ";
        if (!top)
        {
            cout << "EMPTY" << endl;
            return;
        }

        Node *temp = top;
        while (temp)
        {
            cout << temp->data;
            if (temp->prev)
                cout << " <- ";
            temp = temp->prev;
        }
        cout << endl;
    }

    bool isEmpty()
    {
        return !top;
    }

    T peek()
    {
        if (!top)
            return T();
        return top->data;
    }

    ~Stack()
    {
        while (top)
        {
            Node *toDelete = top;
            top = top->prev;
            delete toDelete;
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

    // Validate XML header
    getline(file, line);
    lineNumber++;

    if (line.size() < 5 || line[0] != '<' || line[1] != '?')
    {
        cerr << "Error: Invalid or missing XML header" << endl;
        allGood = false;
    }
    else if (line[line.size() - 1] != '>' || line[line.size() - 2] != '?')
    {
        cerr << "Error: XML header not properly closed" << endl;
        allGood = false;
    }

    // Read XML content line by line
    while (getline(file, line))
    {
        lineNumber++;
        bool insideTag = false;
        bool closingTag = false;
        bool insideAttribute = false;
        bool insideComment = false;
        bool tagNameComplete = false;
        bool commentError = false;
        char commaUsed = '\0';
        string tagName = "";

        for (int i = 0; i < line.length(); i++)
        {
            char c = line[i];

            // Handle comments
            if (insideComment)
            {
                if (c == '-' && i + 1 < line.length() && line[i + 1] == '-')
                {
                    if (i + 2 < line.length() && line[i + 2] == '>')
                    {
                        insideComment = false;
                        i += 2;
                    }
                }
                continue;
            }

            // Opening tag bracket
            if (c == '<')
            {
                if (insideTag)
                {
                    cerr << "Line " << lineNumber << ": Nested '<' found before closing previous tag" << endl;
                    allGood = false;
                }

                // Reset for new tag
                insideTag = true;
                tagName = "";
                closingTag = false;
                tagNameComplete = false;

                // Check for comment
                if (i + 3 < line.length() && line[i + 1] == '!' && line[i + 2] == '-' && line[i + 3] == '-')
                {
                    insideComment = true;
                    insideTag = false;
                    i += 3;
                }
                // Check for closing tag
                else if (i + 1 < line.length() && line[i + 1] == '/')
                {
                    closingTag = true;
                    i++;
                }
            }
            // Closing tag bracket
            else if (c == '>')
            {
                if (!insideTag)
                {
                    cerr << "Line " << lineNumber << ": Found '>' without matching '<'" << endl;
                    allGood = false;
                    continue;
                }

                if (insideAttribute)
                {
                    cerr << "Line " << lineNumber << ": Attribute quote not closed before '>'" << endl;
                    allGood = false;
                }

                // Check for self-closing tag
                if (i > 0 && line[i - 1] == '/')
                {
                    if (!tagName.empty() && tagName[tagName.length() - 1] == '/')
                    {
                        tagName = tagName.substr(0, tagName.length() - 1);
                    }
                    insideTag = false;
                    tagName = "";
                    tagNameComplete = false;
                    continue;
                }

                // cout << endl << "Debug at Line: " << lineNumber << " if c is > before processing tag" << endl;
                // tags.print();

                // Process complete tag
                if (!tagName.empty())
                {
                    if (closingTag)
                    {
                        if (tags.isEmpty())
                        {
                            cerr << "Line " << lineNumber << ": Closing tag '</" << tagName
                                 << ">' has no matching opening tag" << endl;
                            allGood = false;
                        }
                        else
                        {
                            while (!tags.isEmpty())
                            {
                                string expectedTag = tags.pop();
                                int openingLine = tags.getLineNum();
                                if (tagName != expectedTag)
                                {
                                    cerr << "Line " << (openingLine + 1) << ": Closing tag '</" << expectedTag
                                         << ">' is missing." << endl;
                                    allGood = false;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        tags.push(tagName, lineNumber);
                    }
                }

                // cout << endl << "Debug at Line: " << lineNumber << " if c is > after processing tag" << endl;
                // tags.print();

                insideTag = false;
                tagName = "";
                insideAttribute = false;
                tagNameComplete = false;
            }
            // Inside a tag
            else if (insideTag)
            {
                if (insideAttribute)
                {
                    if ((c == '"' || c == '\''))
                    {
                        if (c == commaUsed)
                        {
                            insideAttribute = false;
                            commaUsed = '\0';
                        }
                        else
                        {
                            // Mismatched quotes
                            cerr << "Line " << lineNumber << ": Mismatched quote types in attribute value" << endl;
                            allGood = false;
                            insideAttribute = false;
                            commaUsed = '\0';
                        }
                    }
                }
                else if (c == '=')
                {
                    tagNameComplete = true;

                    // Find opening quote
                    int j = i + 1;
                    while (j < line.length() && isspace(line[j]))
                        j++;

                    if (j < line.length() && (line[j] == '"' || line[j] == '\''))
                    {
                        commaUsed = line[j];
                        insideAttribute = true;
                        i = j;
                    }
                    else
                    {
                        cerr << "Line " << lineNumber << ": Attribute value must be quoted" << endl;
                        allGood = false;
                    }
                }
                else if (c == '/' && i + 1 < line.length() && line[i + 1] == '>')
                {
                    tagName += c;
                }
                else if (!isspace(c))
                {
                    if (!tagNameComplete)
                    {
                        tagName += c;
                    }
                }
                else // Space character
                {
                    if (!tagName.empty())
                    {
                        tagNameComplete = true;
                    }
                }
            }
        }

        // Check for unclosed tag on this line
        if (insideTag)
        {
            cerr << "Line " << lineNumber << ": Tag not closed on this line" << endl;
            allGood = false;
        }

        // Check if comment was not properly closed
        if (insideComment && !commentError)
        {
            cerr << "Line " << lineNumber << ": Comment not properly closed (missing '>')" << endl;
            allGood = false;
            commentError = true;
        }
    }

    // Check for unclosed tags at EOF
    while (!tags.isEmpty())
    {
        int openingLine = tags.getLineNum();
        string unclosedTag = tags.pop();
        cerr << "Error: Tag '<" << unclosedTag << ">' opened at line " << openingLine << " was never closed" << endl;
        allGood = false;
    }

    if (allGood)
    {
        cout << "\nValidation complete: XML is well-formed with no errors!" << endl;
    }
    else
    {
        cout << "\nValidation complete: XML has errors (see above)" << endl;
    }

    file.close();
    return 0;
}