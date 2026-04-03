#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t *produced;
sem_t *consumed;

void *producer(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		sem_wait(produced);
		printf("Data Produced\n");
		sem_post(consumed);
	}
	return NULL;
}

void *consumer(void *arg)
{
	for (int i = 0; i < 5; i++)
	{
		sem_wait(consumed);
		printf("Data Consumed\n");
		sem_post(produced);
	}
	return NULL;
}

int main()
{
	pthread_t tA, tB;
	// sem_init(produced, 0, 1);
	// sem_init(consumed, 0, 0);

	produced = sem_open("/produced", O_CREAT, 0644, 1);
	consumed = sem_open("/consumed", O_CREAT, 0644, 0);

	pthread_create(&tA, NULL, producer, NULL);
	pthread_create(&tB, NULL, consumer, NULL);

	pthread_join(tA, NULL);
	pthread_join(tB, NULL);

	sem_close(produced);
	sem_close(consumed);
	sem_unlink("/produced");
	sem_unlink("/consumed");
	return 0;
}
