#include "function.h"
#include <limits.h>
#include <stdlib.h>

int max(int n, char* arr[])
{
	int largest = INT_MIN;
	for(int i = 1; i < n; i++)
	{
		if(largest < atoi(arr[i]))
			largest = atoi(arr[i]);
	}

	return largest;
}
