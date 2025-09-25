#include <iostream>
#include <limits>
using namespace std;

template <typename T> class Node
{
  public:
	T data;
	Node *prev;
	Node *next;

	Node(T d)
	{
		data = d;
		prev = next = nullptr;
	}
};

template <typename T> class CLL
{
  private:
	Node<T> *head;

  public:
	CLL()
	{
		head = nullptr;
	}

	void clear()
	{
		if (!head)
		{
			return;
		}
		while (head->next != head)
		{
			DeleteFromBeginning();
		}
		delete head;
		head = nullptr;
	}

	void Load(int size)
	{
		clear();
		for (int i = 0; i < size; i++)
		{
			InsertAtEnd(i + 1);
		}
	}

	void InsertAtBeginning(T data)
	{
		Node<T> *temp = new Node<T>(data);
		if (!head)
		{
			head = temp;
			head->next = head;
			head->prev = head;
			return;
		}

		Node<T> *last = head->prev;
		temp->next = head;
		head->prev = temp;
		temp->prev = last;
		last->next = temp;
		head = temp;
	}

	void InsertAtEnd(T data)
	{
		Node<T> *temp = new Node<T>(data);
		if (!head)
		{
			head = temp;
			head->next = head;
			head->prev = head;
			return;
		}

		Node<T> *last = head->prev;
		temp->next = head;
		head->prev = temp;
		temp->prev = last;
		last->next = temp;
	}

	void DeleteFromEnd()
	{
		if (!head)
		{
			return;
		}

		if (head->next == head)
		{
			delete head;
			head = nullptr;
			return;
		}

		Node<T> *lastNode = head->prev;
		Node<T> *newLastNode = lastNode->prev;

		newLastNode->next = head;
		head->prev = newLastNode;
		delete lastNode;
	}

	void DeleteFromBeginning()
	{
		if (!head)
		{
			return;
		}

		if (head->next == head)
		{
			delete head;
			head = nullptr;
			return;
		}

		Node<T> *temp = head->next;
		Node<T> *last = head->prev;

		last->next = temp;
		temp->prev = last;
		delete head;
		head = temp;
	}

	void DeleteValue(T data)
	{
		if (!head)
			return;

		Node<T> *traverse = head;
		do
		{
			if (traverse->data == data)
			{
				if (traverse == head)
				{
					DeleteFromBeginning();
					return;
				}
				else
				{
					traverse->prev->next = traverse->next;
					traverse->next->prev = traverse->prev;
					delete traverse;
					return;
				}
			}
			traverse = traverse->next;
		} while (traverse != head);
	}

	void print()
	{
		if (!head)
		{
			cout << "List is Empty!" << endl;
			return;
		}

		Node<T> *move = head;
		cout << "Circular List: ";
		do
		{
			cout << move->data << " ";
			move = move->next;
		} while (move != head);
		cout << endl;
	}

	int search(T data)
	{
		if (!head)
			return -1;

		Node<T> *traverse = head;
		int c = 0;
		do
		{
			if (traverse->data == data)
			{
				return c;
			}
			traverse = traverse->next;
			c++;
		} while (traverse != head);

		return -1;
	}

	T JP(int k)
	{
		if (!head)
			return T();

		Node<T> *current = head;

		while (current->next != current)
		{
			for (int i = 0; i < k - 1; i++)
			{
				current = current->next;
			}

			Node<T> *nodeToDelete = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;

			if (nodeToDelete == head)
			{
				head = current;
			}
			delete nodeToDelete;
		}

		T index = head->data;
		delete head;
		head = nullptr;
		return index;
	}

	~CLL()
	{
		clear();
	}
};

int main()
{
	CLL<int> myList;
	int choice = 0;

	do
	{
		cout << "\n\t\t\t======= Menu =======\n\n";
		cout << "1. Insert At Beginning\n";
		cout << "2. Insert At End\n";
		cout << "3. Delete From Start\n";
		cout << "4. Delete From End\n";
		cout << "5. Delete by Value\n";
		cout << "6. Display List\n";
		cout << "7. Search element\n";
		cout << "8. Josephus Problem\n";
		cout << "9. Exit\n";
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			int d;
			cout << "Enter Data: ";
			cin >> d;
			myList.InsertAtBeginning(d);
			break;
		}
		case 2:
		{
			int d;
			cout << "Enter Data: ";
			cin >> d;
			myList.InsertAtEnd(d);
			break;
		}
		case 3:
		{
			myList.DeleteFromBeginning();
			break;
		}
		case 4:
		{
			myList.DeleteFromEnd();
			break;
		}
		case 5:
		{
			int d;
			cout << "Enter Value to Delete: ";
			cin >> d;
			myList.DeleteValue(d);
			break;
		}
		case 6:
			myList.print();
			break;
		case 7:
		{
			int val;
			cout << "Enter Value to Search: ";
			cin >> val;
			cout << endl << "Searching Index for Value = " << val << ": " << myList.search(val) << endl;
			break;
		}
		case 8:
		{
			int n, k;

			do
			{
				cout << "Enter number of people (N): ";
				cin >> n;
				if (n <= 0)
				{
					cout << "Number of people must be positive!" << endl;
				}
			} while (n <= 0);

			do
			{
				cout << "Enter step count (k): ";
				cin >> k;
				if (k <= 0)
				{
					cout << "Step count must be positive!" << endl;
				}
			} while (k <= 0);

			CLL<int> josephusList;
			josephusList.Load(n);
			cout << "The last remaining person is at position: " << josephusList.JP(k) << endl;
			break;
		}
		case 9:
			cout << "Exiting..." << endl;
			break;
		default:
			cout << "Invalid input. Please enter a valid choice." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		cout << "\n";
	} while (choice != 9);

	return 0;
}