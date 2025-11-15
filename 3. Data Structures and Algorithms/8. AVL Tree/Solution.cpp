#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template<typename T>
class AVL
{
private:
	class Node
	{
	public:
		Node* left;
		Node* right;
		int height;
		T data;

		Node(T d)
		{
			data = d;
			left = right = nullptr;
			height = 1;
		}
	};

	Node* root;
	int rotationsCount;
	int ll, rr, lr, rl;

	// for AVL

	int Height(Node* temp)
	{
		if (!temp)
			return 0;
		return temp->height;
	}

	Node* rightRotation(Node* x)
	{
		Node* y = x->left;
		Node* T2 = y->right;

		y->right = x;
		x->left = T2;

		x->height = max(Height(x->left), Height(x->right)) + 1;
		y->height = max(Height(y->left), Height(y->right)) + 1;

		rotationsCount++;
		return y;
	}
	Node* leftRotation(Node* x)
	{
		Node* y = x->right;
		Node* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = max(Height(x->left), Height(x->right)) + 1;
		y->height = max(Height(y->left), Height(y->right)) + 1;

		rotationsCount++;
		return y;
	}

	int getBalanceFactor(Node* temp)
	{
		if (!temp)
			return 0;
		return Height(temp->left) - Height(temp->right);
	}

	// recursive Insert helper

	Node* insertNode(Node* temp, T data)
	{
		if (!temp)
			return new Node(data);
		else if (temp->data > data)
		{
			temp->left = insertNode(temp->left, data);
		}
		else if (temp->data < data)
		{
			temp->right = insertNode(temp->right, data);
		}
		else
		{
			return temp;
		}

		temp->height = max(Height(temp->left), Height(temp->right)) + 1;

		int bf = getBalanceFactor(temp);

		if (bf == -2)
		{
			if (data > temp->right->data)
			{
				return RR(temp);
			}
			else
			{
				return RL(temp);
			}
		}
		if (bf == 2)
		{
			if (data < temp->left->data)
			{
				return LL(temp);
			}
			else
			{
				return LR(temp);
			}
		}
		return temp;
	}

	int maxVal(Node* ptr)
	{
		while (ptr->right)
		{
			ptr = ptr->right;
		}
		return ptr->data;
	}

	Node* removeNode(Node* temp, T data)
	{
		if (!temp)
		{
			return nullptr;
		}
	
		else if (temp->data > data)
		{
			temp->left = removeNode(temp->left, data);
		}
		else if (temp->data < data)
		{
			temp->right = removeNode(temp->right, data);
		}
		else
		{
			if (!temp->left)
			{
				Node* r = temp->right;
				delete temp;
				return r;
			}
			else if (!temp->right)
			{
				Node* r = temp->left;
				delete temp;
				return r;
			}
			else
			{
				int h = maxVal(temp->left);
				temp->data = h;
				removeNode(temp->left, h);
			}
		}

		temp->height = max(Height(temp->left), Height(temp->right)) + 1;

		int bf = getBalanceFactor(temp);

		if (bf == -2)
		{
			if (Height(temp->left) < Height(temp->right))
			{
				return RR(temp);
			}
			else
			{
				return RL(temp);
			}
		}
		if (bf == 2)
		{
			if (Height(temp->left) > Height(temp->right))
			{
				return LL(temp);
			}
			else
			{
				return LR(temp);
			}
		}
		return temp;
	}

	Node* LL(Node* temp)
	{
		ll++;
		return rightRotation(temp);
	}

	Node* RR(Node* temp)
	{
		rr++;
		return leftRotation(temp);
	}

	Node* LR(Node* temp)
	{
		lr++;
		temp->left = leftRotation(temp->left);
		return rightRotation(temp);
	}

	Node* RL(Node* temp)
	{
		rl++;
		temp->right = rightRotation(temp->right);
		return leftRotation(temp);
	}

	void clear(Node* p)
	{
		if (!p)
		{
			return;
		}
		clear(p->left);
		clear(p->right);
		delete p;
	}

public:
	AVL()
	{
		root = nullptr;
		rotationsCount = 0;
		lr = rr = ll = rl = 0;
	}

	// recursive Insert

	void insert(T data)
	{
		root = insertNode(root, data);
	}

	void remove(T data)
	{
		root = removeNode(root, data);
	}
	
	void levelOrderTraversal()
	{
		cout << endl << "Level Order Traversal: ";
		if (!root)
		{
			cout << "Tree is Empty" << endl;
			return;
		}

		queue<Node*> q;
		q.push(root);

		while (!q.empty())
		{
			Node* temp = q.front();
			q.pop();

			cout << "Data: " << temp->data << " Key: " << temp->height << ", " << getBalanceFactor(temp) << " --> ";


			if (temp->left)
			{
				q.push(temp->left);
			}
			if (temp->right)
			{
				q.push(temp->right);
			}
		}
	}

	void dfs()
	{
		cout << endl << "DFS Traversal: ";
		if (!root)
		{
			cout << "Tree is Empty" << endl;
			return;
		}

		stack<Node*> s;
		s.push(root);

		while (!s.empty())
		{
			Node* temp = s.top();
			s.pop();

			cout << "Data: " << temp->data << " Key: " << temp->height << ", " << getBalanceFactor(temp) << " --> ";


			if (temp->left)
			{
				s.push(temp->left);
			}
			if (temp->right)
			{
				s.push(temp->right);
			}
		}
	}

	void getRotationsCount()
	{
		cout << endl << "Total Rotaions: " << rotationsCount << endl;
		cout << endl << "LL: " << (ll+1) << endl;
		cout << endl << "LR: " << lr << endl;
		cout << endl << "RL: " << rl << endl;
		cout << endl << "RR: " << (rr+1) << endl;
		
	}

	~AVL()
	{
		clear(root);
	}
};

template <typename T, int K>
class BFS
{
private:
	T adjacency[K][K];
	T values[K];
	int current;
	int rootIndex;
public:
	BFS()
	{
		for (int i = 0; i < K; i++)
		{
			values[i] = 0;
		}
		rootIndex = -1;
		current = 0;
		
		for (int i = 0; i <= K; i++)
		{
			for (int j = 0; j < K; j++)
			{
				adjacency[i][j] = 0;
			}
		}
	}

	void insertRoot(T data)
	{
		rootIndex = 0;
		if (current < K)
		{
			values[current] = data;
			current++;
		}
	}

	void insertChild(int index, T data)
	{
		if (current < K)
		{
			values[current] = data;
			adjacency[index][current++] = 1;
		}
	}

	void bfs()
	{
		cout << endl << "BFS Traversal: ";
		if (rootIndex == -1)
		{
			cout << "Tree is Empty" << endl;
			return;
		}

		queue<int> q;
		q.push(rootIndex);

		while (!q.empty())
		{
			cout << values[q.front()] << " - ";
			for (int i = 0; i < current; i++)
			{
				if (adjacency[q.front()][i] == 1)
				{
					q.push(i);
				}
			}
			q.pop();
		}
	}
};


int main()
{
	// Part 1

	cout << endl << " ======= PART 1 ======= " << endl;

	AVL<int> t;

	t.insert(10);
	t.insert(20);
	t.insert(30);
	t.insert(40);
	t.insert(50);
	t.insert(25);

	t.levelOrderTraversal();

	t.remove(30);
	t.levelOrderTraversal();

	t.getRotationsCount();

	cout << endl << " ======= PART 2 ======= " << endl;
	BFS<int,5> b;
	b.insertRoot(5);
	b.insertChild(0,7);
	b.insertChild(0, 12);

	b.insertChild(1, 15);
	b.insertChild(1, 21);

	b.insertChild(2, 2);
	b.insertChild(2,4);
	b.bfs();


	cout << endl << " ======= PART 2 ======= " << endl;

	t.dfs();

	return 0;
}