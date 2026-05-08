#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEM_B "/sem_b"
#define SEM_C "/sem_c"

int main()
{
	// Open semaphores
	// sem_b is used to wait for Process A
	// sem_c controls Process C (starts with 0)
	sem_t *sem_b = sem_open(SEM_B, O_CREAT, 0666, 0);
	sem_t *sem_c = sem_open(SEM_C, O_CREAT, 0666, 0);

	if (sem_b == SEM_FAILED || sem_c == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}

	// Process B waits for Process A to signal
	printf("Process B: Waiting for Process A...\n");
	sem_wait(sem_b);

	// Perform task
	printf("Process B: Executing task (ID: %d)\n", getpid());
	printf("Process B: Sleeping for 2 seconds...\n");
	sleep(2);
	printf("Process B: Task completed!\n");

	// Signal Process C to start
	printf("Process B: Signaling Process C...\n");
	sem_post(sem_c);

	sem_close(sem_b);
	sem_close(sem_c);

	return 0;
}
