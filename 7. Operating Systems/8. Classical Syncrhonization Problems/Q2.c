#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PHILOSOPHERS 5

sem_t forks[PHILOSOPHERS];

void *philosopher(void *arg)
{
	int id = *(int *) arg;
	int left_fork = id;
	int right_fork = (id + 1) % PHILOSOPHERS;

	// To avoid deadlock
	int first_fork = (left_fork < right_fork) ? left_fork : right_fork;
	int second_fork = (left_fork < right_fork) ? right_fork : left_fork;

	printf("Philosopher %d is thinking...\n", id);
	// sleep(1);

	printf("Philosopher %d is hungry, waiting for forks...\n", id);

	// Pick up first fork
	sem_wait(&forks[first_fork]);
	printf("Philosopher %d picked up fork %d\n", id, first_fork);

	// Pick up second fork
	sem_wait(&forks[second_fork]);
	printf("Philosopher %d picked up fork %d, now EATING!\n", id, second_fork);

	// sleep(1);

	// Put forks down in reverse order
	sem_post(&forks[second_fork]);
	sem_post(&forks[first_fork]);
	printf("Philosopher %d put down forks, done eating\n", id);

	return NULL;
}

int main()
{
	pthread_t threads[PHILOSOPHERS];
	int ids[PHILOSOPHERS];

	// Initialize forks (each as available)
	for (int i = 0; i < PHILOSOPHERS; i++)
	{
		sem_init(&forks[i], 0, 1);
	}

	for (int i = 0; i < PHILOSOPHERS; i++)
	{
		ids[i] = i;
		pthread_create(&threads[i], NULL, philosopher, &ids[i]);
	}

	for (int i = 0; i < PHILOSOPHERS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	// Clean up
	for (int i = 0; i < PHILOSOPHERS; i++)
	{
		sem_destroy(&forks[i]);
	}

	printf("All philosophers are done!\n");
	return 0;
}
