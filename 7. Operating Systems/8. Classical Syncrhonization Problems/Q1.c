#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 2
#define NUM_CONSUMERS 2

int buffer[BUFFER_SIZE];
int in = 0;  // Position to insert
int out = 0; // Position to extract

sem_t lock, empty, full;

void *producer(void *arg)
{
	int id = *(int *) arg;

	for (int i = 0; i < 3; i++)
	{
		int item = in * 100;

		sem_wait(&empty); // Wait if buffer full
		sem_wait(&lock);  // Lock buffer

		buffer[in] = item;
		printf("Producer %d produced: %d at position %d\n", id, item, in);
		in = (in + 1) % BUFFER_SIZE;

		sem_post(&lock); // Unlock buffer
		sem_post(&full); // Signal item available

		sleep(1);
	}
	return NULL;
}

void *consumer(void *arg)
{
	int id = *(int *) arg;

	for (int i = 0; i < 3; i++)
	{
		sem_wait(&full); // Wait if buffer empty
		sem_wait(&lock); // Lock buffer

		int item = buffer[out];
		printf("Consumer %d consumed: %d from position %d\n", id, item, out);
		out = (out + 1) % BUFFER_SIZE;

		sem_post(&lock);  // Unlock buffer
		sem_post(&empty); // Signal slot now empty

		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t producers[NUM_PRODUCERS], consumers[NUM_CONSUMERS];
	int prod_ids[NUM_PRODUCERS], cons_ids[NUM_CONSUMERS];

	sem_init(&lock, 0, 1);
	sem_init(&empty, 0, BUFFER_SIZE); // Count of empty slots
	sem_init(&full, 0, 0);            // Count of full slots

	for (int i = 0; i < NUM_PRODUCERS; i++)
	{
		prod_ids[i] = i;
		pthread_create(&producers[i], NULL, producer, &prod_ids[i]);
	}

	for (int i = 0; i < NUM_CONSUMERS; i++)
	{
		cons_ids[i] = i;
		pthread_create(&consumers[i], NULL, consumer, &cons_ids[i]);
	}

	for (int i = 0; i < NUM_PRODUCERS; i++)
	{
		pthread_join(producers[i], NULL);
	}

	for (int i = 0; i < NUM_CONSUMERS; i++)
	{
		pthread_join(consumers[i], NULL);
	}

	sem_destroy(&lock);
	sem_destroy(&empty);
	sem_destroy(&full);

	printf("Done!\n");
	return 0;
}
