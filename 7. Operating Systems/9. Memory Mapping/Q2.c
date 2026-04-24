#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int *counter = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (counter == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}

	*counter = 0;
	pid_t pid1 = fork();

	if (pid1 == 0)
	{
		// child 1
		for (int i = 0; i < 5; i++)
		{
			(*counter)++;
			printf("Child 1 incremented counter to: %d\n", *counter);
		}
	}
	else if (pid1 > 0)
	{
		// parent
		waitpid(pid1, NULL, 0);

		pid_t pid2 = fork();

		if (pid2 == 0)
		{
			// child 2
			for (int i = 0; i < 5; i++)
			{
				(*counter)++;
				printf("Child 2 incremented counter to: %d\n", *counter);
			}
		}
		else if (pid2 > 0)
		{
			// parent
			waitpid(pid2, NULL, 0);

			printf("Value of counter in parent: %d\n", *counter);
		}
		else
		{
			perror("fork failed");
			exit(1);
		}
	}
	else
	{
		perror("fork failed");
		exit(1);
	}

	if (munmap(counter, sizeof(int)) == -1)
	{
		perror("munmap");
		exit(1);
	}

	return 0;
}