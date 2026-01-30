#include <stdio.h>
#include "function.h"

int main(int argc, char* arg[])
{
	int mymin = min(argc, arg);
	int mymax = max(argc, arg);
	float myavg = avg(argc, arg);
	int mysum = sum(argc, arg);

	printf("Sum of Array: %d\n", mysum);
	printf("Minimum Value: %d\n", mymin);
	printf("Maximum Value: %d\n", mymax);
	printf("Average Value: %.2f\n", myavg);

	return 0;
}
