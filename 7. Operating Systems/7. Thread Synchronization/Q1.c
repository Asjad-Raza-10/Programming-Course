#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int balance;
pthread_mutex_t lock;

void *withdraw_no_mutex(void *arg)
{
	int amount = *(int *) arg;
	for (int i = 0; i < 1000; i++)
	{
		if (balance >= amount)
		{
			int temp = balance;
			usleep(1); // make race condition visible
			balance = temp - amount;
		}
	}
	return NULL;
}

void *withdraw_with_mutex(void *arg)
{
	int amount = *(int *) arg;
	for (int i = 0; i < 1000; i++)
	{
		pthread_mutex_lock(&lock);
		if (balance >= amount)
		{
			int temp = balance;
			usleep(1);
			balance = temp - amount;
		}
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

int main()
{
	pthread_t t1, t2;
	int amount = 1;

	// Race condition version
	balance = 2000;
	pthread_create(&t1, NULL, withdraw_no_mutex, &amount);
	pthread_create(&t2, NULL, withdraw_no_mutex, &amount);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("[No Mutex] Final balance = %d (expected 0, likely incorrect)\n", balance);

	// Mutex version
	balance = 2000;
	pthread_mutex_init(&lock, NULL);
	pthread_create(&t1, NULL, withdraw_with_mutex, &amount);
	pthread_create(&t2, NULL, withdraw_with_mutex, &amount);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("[With Mutex] Final balance = %d (expected 0)\n", balance);

	pthread_mutex_destroy(&lock);
	return 0;
}
