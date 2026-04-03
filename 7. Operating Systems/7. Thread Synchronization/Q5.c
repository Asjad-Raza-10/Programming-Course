#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#define N 5
sem_t *sem_in[N];
sem_t *sem_out[N];

void *worker(void *arg)
{
	int id = *(int *) arg;
	int idx = id - 1;

	char in_name[32];
	char out_name[32];
	if (idx == 0)
	{
		strcpy(in_name, "/sem_in_0");
	}
	else
	{
		sprintf(in_name, "/sem_in_%d", idx);
	}
	if (idx == 0)
	{
		strcpy(out_name, "/sem_out_0");
	}
	else
	{
		sprintf(out_name, "/sem_out_%d", idx);
	}

	sem_t *sem_in_ptr = sem_open(in_name, 0);
	sem_t *sem_out_ptr = sem_open(out_name, 0);

	while (1)
	{
		sem_wait(sem_in_ptr);
		printf("I am in %d\n", id);
		if (idx < N - 1)
		{
			sem_post(sem_in[idx + 1]);
		}
		else
		{
			sem_post(sem_out[0]);
		}

		sem_wait(sem_out_ptr);
		printf("I am out %d\n", id);
		if (idx < N - 1)
		{
			sem_post(sem_out[idx + 1]);
		}
		else
		{
			sem_post(sem_in[0]);
		}
	}

	sem_close(sem_in_ptr);
	sem_close(sem_out_ptr);
	return NULL;
}

int main()
{
	pthread_t threads[N];
	int ids[N];

	for (int i = 0; i < N; i++)
	{
		ids[i] = i + 1;
		char name[32];
		if (i == 0)
			strcpy(name, "/sem_in_0");
		else
			sprintf(name, "/sem_in_%d", i);
		sem_unlink(name);
		sem_in[i] = sem_open(name, O_CREAT | O_EXCL, 0644, (i == 0) ? 1 : 0);

		if (i == 0)
			strcpy(name, "/sem_out_0");
		else
			sprintf(name, "/sem_out_%d", i);
		sem_unlink(name);
		sem_out[i] = sem_open(name, O_CREAT | O_EXCL, 0644, 0);
	}

	for (int i = 0; i < N; i++)
	{
		pthread_create(&threads[i], NULL, worker, &ids[i]);
	}

	for (int i = 0; i < N; i++)
	{
		pthread_join(threads[i], NULL);
	}

	for (int i = 0; i < N; i++)
	{
		char name[32];
		if (i == 0)
			strcpy(name, "/sem_in_0");
		else
			sprintf(name, "/sem_in_%d", i);
		sem_close(sem_in[i]);
		sem_unlink(name);

		if (i == 0)
			strcpy(name, "/sem_out_0");
		else
			sprintf(name, "/sem_out_%d", i);
		sem_close(sem_out[i]);
		sem_unlink(name);
	}

	return 0;
}
