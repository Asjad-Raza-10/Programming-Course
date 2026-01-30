#include "function.h"
#include <limits.h>
#include <stdlib.h>

int min(int n, char* arr[])
{
	int smallest = INT_MAX;
	for(int i = 1; i < n; i++)
	{
		if(smallest > atoi(arr[i]))
			smallest = atoi(arr[i]);
	}

	return smallest;
}
