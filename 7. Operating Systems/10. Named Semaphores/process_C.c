#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#define SEM_C "/sem_c"

int main()
{
	// Open semaphore
	// sem_c is used to wait for Process B
	sem_t *sem_c = sem_open(SEM_C, O_CREAT, 0666, 0);

	if (sem_c == SEM_FAILED)
	{
		perror("sem_open");
		exit(1);
	}

	// Process C waits for Process B to signal
	printf("Process C: Waiting for Process B...\n");
	sem_wait(sem_c);

	// Perform task
	printf("Process C: Executing task (ID: %d)\n", getpid());
	printf("Process C: Sleeping for 2 seconds...\n");
	sleep(2);
	printf("Process C: Task completed!\n");

	sem_close(sem_c);

	sem_unlink("/sem_a");
	sem_unlink("/sem_b");
	sem_unlink("/sem_c");

	return 0;
}
