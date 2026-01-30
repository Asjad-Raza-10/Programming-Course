#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*arg[])
{
	int n = 0;

	printf("Enter the number of entries: ");
	scanf("%d", &n);
	int arr[n];
	
	for(int i = 1; i <= n; i++)
	{
		if(i == 1)
		{
			printf("Enter the 1st number: ");
			scanf("%d", &arr[i-1]);	
		}
		else if(i == 2)
		{
			printf("Enter the 2nd number: ");
			scanf("%d", &arr[i-1]);
		}
		else if(i == 3)
		{
			printf("Enter the 3rd number: ");
			scanf("%d", &arr[i-1]);
		}
		else
		{
			printf("Enter the %dth number: ", i);
			scanf("%d", &arr[i-1]); 
		}
	}

	int largest = 0;
	for(int i = 0; i < n; i++)
	{
		if(largest < arr[i])
			largest = arr[i];
	}

	printf("Largest Number is: %d\n", largest);

	return 0;
}
