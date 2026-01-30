#include "function.h"
#include <stdlib.h>

float avg(int n, char* arr[])
{
	float sum = 0;
	for(int i = 1; i < n; i++)
	{
		sum += atoi(arr[i]);
	}

	return sum/n;
}
