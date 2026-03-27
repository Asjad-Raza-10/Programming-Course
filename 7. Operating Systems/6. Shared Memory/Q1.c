#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *printNumbers(void *arg)
{
	int n = *(int *) arg;

	printf("Simple Numbers: ");
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", i);
	}
	printf("\n");
	return NULL;
}

void *printFibonacci(void *arg)
{
	int n = *(int *) arg;
	int a = 0, b = 1, c;

	printf("Fibonacci sequence: ");
	for (int i = 1; i <= n; i++)
	{
		printf("%d ", a);
		c = a + b;
		a = b;
		b = c;
	}
	printf("\n");
	return NULL;
}

void *printPrimeNumbers(void *arg)
{
	int n = *(int *) arg;

	printf("Prime numbers: ");
	for (int i = 2; i <= n; i++)
	{
		int isPrime = 1;
		for (int j = 2; j <= i / 2; j++)
		{
			if (i % j == 0)
			{
				isPrime = 0;
				break;
			}
		}
		if (isPrime)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		perror("Incorrect input brotherrr!");
		exit(EXIT_FAILURE);
	}

	int num = atoi(argv[1]);

	printf("Given number: %d\n", num);

	pthread_t thread1, thread2, thread3;

	pthread_create(&thread1, NULL, printNumbers, &num);
	pthread_join(thread1, NULL);

	pthread_create(&thread2, NULL, printFibonacci, &num);
	pthread_join(thread2, NULL);

	pthread_create(&thread3, NULL, printPrimeNumbers, &num);
	pthread_join(thread3, NULL);

	return 0;
}