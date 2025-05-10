#include <iostream>
using namespace std;

void updateValue(int*& ptr, int NewValue)
{
	if (ptr == nullptr)
	{
		ptr = new int(NewValue);
	}
	*ptr = NewValue;
}

int main()
{
	int* ptr = nullptr;

	updateValue(ptr, 45);
	cout << "Pointer ptr point to " << *ptr << " at address " << ptr << endl;
	updateValue(ptr, 72);
	cout << "Pointer ptr point to " << *ptr << " at address " << ptr << endl;

	delete ptr;
	ptr = nullptr;

	return 0;
}