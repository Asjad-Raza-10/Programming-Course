#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
	int *var = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	*var = 10;

	if (var == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}

	pid_t pid = fork();

	if (pid == 0)
	{
		// child
		*var = 99;
	}
	else if (pid > 0)
	{
		// parent
		wait(NULL);
		printf("Value of var in parent: %d\n", *var);

		if (munmap(var, sizeof(int)) == -1)
		{
			perror("munmap");
			exit(1);
		}
	}
	else
	{
		perror("fork failed");
		exit(1);
	}

	return 0;
}