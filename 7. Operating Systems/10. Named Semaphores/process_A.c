#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEM_A "/sem_a"
#define SEM_B "/sem_b"

int main()
{
	// Open/Create semaphores
	// sem_a controls process A (starts with 1)
	// sem_b controls process B (starts with 0)
	sem_t *sem_a = sem_open(SEM_A, O_CREAT, 0666, 1);
	sem_t *sem_b = sem_open(SEM_B, O_CREAT, 0666, 0);

	if (sem_a == SEM_FAILED || sem_b == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}

	// Process A waits for its turn
	sem_wait(sem_a);

	// Perform task
	printf("Process A: Executing task (ID: %d)\n", getpid());
	printf("Process A: Sleeping for 2 seconds...\n");
	sleep(2);
	printf("Process A: Task completed!\n");

	// Signal Process B to start
	printf("Process A: Signaling Process B...\n");
	sem_post(sem_b);

	sem_close(sem_a);
	sem_close(sem_b);

	return 0;
}
