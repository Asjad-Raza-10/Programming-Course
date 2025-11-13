#include <iostream>
using namespace std;

class MaxHeap
{
	int *arr;
	int size;
	int curr;

  public:
	MaxHeap(int s = 5)
	{
		size = s;
		arr = new int[size];
		curr = 0;
	}

	void insert(int data)
	{
		if (curr < size)
		{
			arr[curr] = data;
			heapifyUp(curr); // Use heapifyUp
			curr++;
		}
	}

	int leftChild(int i)
	{
		if ((i * 2 + 1) < curr)
		{
			return i * 2 + 1;
		}
		return -1;
	}

	int rightChild(int i)
	{
		if ((i * 2 + 2) < curr)
		{
			return i * 2 + 2;
		}
		return -1;
	}

	int parent(int i)
	{
		if (i > 0)
		{
			return (i - 1) / 2;
		}
		return -1;
	}

	int max(int x, int y)
	{
		if (arr[x] > arr[y])
		{
			return x;
		}
		return y;
	}

	int deleteData()
	{
		int temp = arr[0];
		arr[0] = arr[curr - 1];
		curr--;
		heapifyDown(0); // Heapify down from root
		return temp;
	}

	// for deletion (bubbles element down)
	void heapifyDown(int i)
	{
		while (i < curr)
		{
			int leftIndex = leftChild(i);
			int rightIndex = rightChild(i);

			if (leftIndex != -1 && rightIndex != -1)
			{
				int largest = max(leftIndex, rightIndex);
				if (arr[largest] > arr[i])
				{
					swap(arr[largest], arr[i]);
					i = largest;
				}
				else
				{
					break;
				}
			}
			else if (leftIndex != -1 && rightIndex == -1)
			{
				if (arr[leftIndex] > arr[i])
				{
					swap(arr[leftIndex], arr[i]);
					i = leftIndex;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}

	// for insertion or update (bubbles element up)
	void heapifyUp(int i)
	{
		while (i > 0)
		{
			int parentIndex = parent(i);
			if (parentIndex != -1 && arr[i] > arr[parentIndex])
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
		cout << endl;
		for (int i = 0; i < curr; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void update(int index, int value)
	{
		if (index >= 0 && index < curr)
		{
			arr[index] = value;
		}
	}

	void heapify()
	{
		// Start from last non-leaf node and heapify down
		for (int i = curr / 2 - 1; i >= 0; i--)
		{
			heapifyDown(i);
		}
	}

	// for heap sort
	void addToEnd(int val)
	{
		arr[curr++] = val;
	}

	~MaxHeap()
	{
		delete[] arr;
		arr = nullptr;
	}
};

class MinHeap
{
	int *arr;
	int size;
	int curr;

  public:
	MinHeap(int s = 5)
	{
		size = s;
		arr = new int[size];
		curr = 0;
	}

	void insert(int data)
	{
		if (curr < size)
		{
			arr[curr] = data;
			heapifyUp(curr);
			curr++;
		}
	}

	int leftChild(int i)
	{
		if ((i * 2 + 1) < curr)
		{
			return i * 2 + 1;
		}
		return -1;
	}

	int rightChild(int i)
	{
		if ((i * 2 + 2) < curr)
		{
			return i * 2 + 2;
		}
		return -1;
	}

	int parent(int i)
	{
		if (i > 0)
		{
			return (i - 1) / 2;
		}
		return -1;
	}

	int min(int x, int y)
	{
		if (arr[x] < arr[y])
		{
			return x;
		}
		return y;
	}

	int deleteData()
	{
		int temp = arr[0];
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

			if (leftIndex != -1 && rightIndex != -1)
			{
				int smallest = min(leftIndex, rightIndex);
				if (arr[smallest] < arr[i])
				{
					swap(arr[smallest], arr[i]);
					i = smallest;
				}
				else
				{
					break;
				}
			}
			else if (leftIndex != -1 && rightIndex == -1)
			{
				if (arr[leftIndex] < arr[i])
				{
					swap(arr[leftIndex], arr[i]);
					i = leftIndex;
				}
				else
				{
					break;
				}
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
			if (parentIndex != -1 && arr[i] < arr[parentIndex])
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
		cout << endl;
		for (int i = 0; i < curr; i++)
		{
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	void update(int index, int value)
	{
		if (index >= 0 && index < curr)
		{
			arr[index] = value;
		}
	}

	void heapify()
	{
		// Start from last non-leaf node and heapify down
		for (int i = curr / 2 - 1; i >= 0; i--)
		{
			heapifyDown(i);
		}
	}

	~MinHeap()
	{
		delete[] arr;
		arr = nullptr;
	}
};

// we can do this inside the heap class too, i just chose to do it over here
void heapSort(int *arr, int size)
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

int main()
{
	// Question 2
	cout << endl << "======= Question 2 =======" << endl;
	MaxHeap mxH(7);
	mxH.insert(10);
	mxH.insert(20);
	mxH.insert(5);
	mxH.insert(6);
	mxH.insert(1);
	mxH.insert(8);
	mxH.insert(9);
	cout << "Max Heap is:";
	mxH.print();

	// Question 3
	cout << endl << "======= Question 3 =======" << endl;
	MinHeap mnH(7);
	mnH.insert(10);
	mnH.insert(20);
	mnH.insert(5);
	mnH.insert(6);
	mnH.insert(1);
	mnH.insert(8);
	mnH.insert(9);
	cout << "Min Heap is:";
	mnH.print();

	// Question 4
	cout << endl << "======= Question 4 =======" << endl;
	cout << "Updating a value in Max Heap" << endl;
	mxH.update(4, 105);
	cout << "Max Heap before heapify function:";
	mxH.print();
	cout << "Max Heap after heapify function:";
	mxH.heapify();
	mxH.print();

	cout << endl;

	cout << "Updating a value in Min Heap" << endl;
	mnH.update(4, 2);
	cout << "Min Heap before heapify function:";
	mnH.print();
	cout << "Min Heap after heapify function:";
	mnH.heapify();
	mnH.print();

	// Question 5
	cout << endl << "======= Question 5 =======" << endl;
	cout << "Deleting number from Min Heap" << endl;
	cout << "Deleted number is : " << mxH.deleteData() << endl;
	cout << "Max heap now:";
	mxH.print();

	cout << endl;

	cout << "Deleting number from Min Heap" << endl;
	cout << "Deleted number is : " << mnH.deleteData() << endl;
	cout << "Min heap now:";
	mnH.print();

	// Question 6
	cout << endl << "======= Question 6 =======" << endl;
	const int size = 6;
	int arr[size] = {10, 3, 5, 1, 4, 2};

	cout << "Array before Heap Sort: ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	heapSort(arr, size);

	cout << "Array after Heap Sort: ";
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;

	return 0;
}