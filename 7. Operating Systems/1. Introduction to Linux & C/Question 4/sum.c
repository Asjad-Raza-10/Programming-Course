#include "function.h"
#include <stdlib.h>

int sum(int n, char* arr[])
{
	int sum = 0;
	for(int i = 1; i < n; i++)
	{
		sum += atoi(arr[i]);
	}

	return sum;
}
