#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define STUDENTS 7
sem_t *computers;

void *student(void *arg)
{
	int id = *(int *) arg;
	sem_wait(computers);
	printf("Student %d sits on computer\n", id);
	sleep(2);
	printf("Student %d leaves computer\n", id);
	sem_post(computers);
	return NULL;
}

int main()
{
	pthread_t threads[STUDENTS];
	int ids[STUDENTS];

	computers = sem_open("/computers", O_CREAT, 0644, 3);
	for (int i = 0; i < STUDENTS; i++)
	{
		ids[i] = i + 1;
		pthread_create(&threads[i], NULL, student, &ids[i]);
	}

	for (int i = 0; i < STUDENTS; i++)
	{
		pthread_join(threads[i], NULL);
	}

	sem_close(computers);
	sem_unlink("/computers");
	return 0;
}
