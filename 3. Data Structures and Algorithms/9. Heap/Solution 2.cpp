#include <iostream>
#include <vector>
using namespace std;

class MaxHeap
{
	int* arr;
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
	int* arr;
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
void heapSortAscending(int* arr, int size)
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

void heapSortDescending(int* arr, int size)
{
	MinHeap m(size);
	for (int i = 0; i < size; i++)
	{
		m.insert(arr[i]);
	}

	for (int i = size - 1; i >= 0; i--)
	{
		arr[i] = m.deleteData();
	}
}


void buildMaxHeap(int* arr, int size, MaxHeap& mxH)
{
	for (int i = 0; i < size; i++)
	{
		mxH.insert(arr[i]);
	}
	cout << "Max Heap was built" << endl;
	cout << "Max Heap is:";
	mxH.print();
}

void buildMinHeap(int* arr, int size, MinHeap& mnH)
{
	for (int i = 0; i < size; i++)
	{
		mnH.insert(arr[i]);
	}
	cout << "Min Heap was built" << endl;
	cout << "Min Heap is:";
	mnH.print();
}

void maxHeapAlgo(vector<int> &arr)
{
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		bool flag = true;
		for (int j = ((i - 1) / 2); flag; j /= 2)
		{
			if (!j)
			{
				flag = false;
			}
			if (arr[i] > arr[j])
			{
				swap(arr[i], arr[j]);
			}
			else
			{
				flag = false;
			}
		}
	}
}


void minHeapAlgo(vector<int>& arr)
{
	for (int i = arr.size() - 1; i >= 0; i--)
	{
		bool flag = true;
		for (int j = ((i - 1) / 2); flag; j /= 2)
		{
			if (!j)
			{
				flag = false;
			}
			if (arr[i] < arr[j])
			{
				swap(arr[i], arr[j]);
			}
			else
			{
				flag = false;
			}
		}
	}
}

// Question 4
class MinPriorityQueue
{
private:
	MinHeap mnH;

public:
	MinPriorityQueue(int size = 5) : mnH(size) {}

	void enqueue(int d)
	{
		mnH.insert(d);
	}

	int dequeue()
	{
		return mnH.deleteData();
	}

	void print()
	{
		cout << "Minimum Priority Queue is: ";
		mnH.print();
	}
};

class MaxPriorityQueue
{
private:
	MaxHeap mxH;

public:
	MaxPriorityQueue(int size = 5) : mxH(size) {}

	void enqueue(int d)
	{
		mxH.insert(d);
	}

	int dequeue()
	{
		return mxH.deleteData();
	}

	void print()
	{
		cout << "Minimum Priority Queue is: ";
		mxH.print();
	}
};

int main()
{
	// Question 1
	cout << endl << "======= Question 1 =======" << endl;
	int arr[6] = { 30, 20, 40, 10, 50, 60 };
	MaxHeap mxH(7);
	buildMaxHeap(arr, 6, mxH);

	cout << "Inserting 35" << endl;
	mxH.insert(35);
	cout << "Max Heap is:";
	mxH.print();

	cout << "Deleting root from Max Heap" << endl;
	cout << "Deleted value is : " << mxH.deleteData() << endl;
	cout << "Max heap now:";
	mxH.print();

	// Question 2
	cout << endl << "======= Question 2 =======" << endl;
	int arr2[6] = { 9, 5, 4, 1, 7, 3 };
	MinHeap mnH(7);
	buildMinHeap(arr2, 6, mnH);

	cout << "Inserting 2" << endl;
	mnH.insert(2);
	cout << "Min Heap is:";
	mnH.print();

	cout << "Deleting root from Min Heap" << endl;
	cout << "Deleted value is : " << mnH.deleteData() << endl;
	cout << "Min heap now:";
	mnH.print();

	// Question 3
	cout << endl << "======= Question 3 =======" << endl;
	int arr3[7] = { 19, 3, 15, 7, 8, 23, 74 };
	cout << "Array before Ascending Heap Sort: ";
	for (int i = 0; i < 7; i++)
	{
		cout << arr3[i] << " ";
	}
	heapSortAscending(arr3, 7);
	cout << endl << "Array after Ascending Heap Sort: ";
	for (int i = 0; i < 7; i++)
	{
		cout << arr3[i] << " ";
	}

	int arr4[7] = { 10, 23, 5, 76, 8, 42, 11 };
	cout << endl << endl << "Array before Descending Heap Sort: ";
	for (int i = 0; i < 7; i++)
	{
		cout << arr4[i] << " ";
	}
	heapSortDescending(arr4, 7);
	cout << endl << "Array after Descending Heap Sort: ";
	for (int i = 0; i < 7; i++)
	{
		cout << arr4[i] << " ";
	}

	// Question 4 class implemented right above the main

	// Question 5
	cout << endl << "======= Question 5 =======" << endl;
	vector<int> v1 = { 40, 10, 30, 5, 60, 15 };
	cout << "Array before Max Heap Algo: ";
	for (int i : v1)
	{
		cout << i << " ";
	}
	maxHeapAlgo(v1);
	cout << endl << "Array after Max Heap Algo: ";
	for (int i : v1)
	{
		cout << i << " ";
	}

	vector<int> v2 = { 10, 2, 15, 20, 5, 1 };
	cout << endl << endl << "Array before Min Heap Algo: ";
	for (int i : v2)
	{
		cout << i << " ";
	}
	minHeapAlgo(v2);
	cout << endl << "Array after Min Heap Algo: ";
	for (int i : v2)
	{
		cout << i << " ";
	}
	
	cout << endl;

	return 0;
}