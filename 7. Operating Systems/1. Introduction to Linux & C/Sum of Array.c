#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*arg[])
{
	int sum = 0;
	for(int i = 1; i < argc; i++)
	{
		sum += atoi(arg[i]);
	}

	printf("Sum: %d\n", sum);

	return 0;
}
