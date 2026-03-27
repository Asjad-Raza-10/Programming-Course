#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		perror("Incorrect input brotherrr!");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]); // Size of Array
	int m = atoi(argv[2]); // Number of Forks

	int SHM_SIZE = n + m;

	printf("Size of Array: %d \n", n);
	printf("Number of Forks : %d \n", m);

	// create N size array with random numbers
	int *arr = (int *) malloc(n * sizeof(int));
	if (arr == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}

	printf("Generated array: ");
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100; // Random numbers between 0 and 99
		printf("%d ", arr[i]);
	}
	printf("\n");

	// Generate a unique key for shared memory for array
	key_t key = ftok("shmfile", 65);

	// Create a shared memory segment
	int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
	if (shmid == -1)
	{
		perror("shmget failed");
		exit(EXIT_FAILURE);
	}

	// Attach to the shared memory
	int *data = (int *) shmat(shmid, NULL, 0);
	if (data == (int *) (-1))
	{
		perror("shmat failed");
		exit(EXIT_FAILURE);
	}

	// Write text to shared memory
	memcpy(data, arr, n * sizeof(int));
	printf("Process 1: Written array to shared memory\n");

	for (int i = 0; i < m; i++)
	{
		if (fork() == 0)
		{
			// Child process
			printf("Child process %d created\n", getpid());

			// Each child process should:
			//  • Compute the sum of a subset of the array ( divide the array into M equal parts).
			//  • Write its partial sum into the shared memory segment at the appropriate index.
			//  • Exit after writing the partial sum.

			int start = i * (n / m);
			int end = (i + 1) * (n / m) - 1;
			int sum = 0;
			for (int j = start; j <= end; j++)
			{
				sum += arr[j];
			}

			data[i + 1] = sum; // Write partial sum to shared memory
			printf("Child process %d computed sum: %d\n", getpid(), sum);

			exit(0); // Exit child process
		}
	}

	// The main process should:
	//  • Wait for all child processes to complete.
	//  • Read the partial sums from the shared memory and compute the final sum.
	//  • Print the final sum.
	//  • Detach and delete the shared memory segment.

	// Wait for all child processes to complete
	for (int i = 0; i < m; i++)
	{
		wait(NULL);
	}

	// Read the partial sums from the shared memory and compute the final sum
	int final_sum = 0;
	for (int i = 1; i <= m; i++)
	{
		final_sum += data[i];
	}
	printf("Final sum: %d\n", final_sum);

	// Detach from shared memory
	if (shmdt(data) == -1)
	{
		perror("shmdt");

		exit(1);
	}
	// Delete the shared memory segment
	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("shmctl");
		exit(1);
	}
	printf("Process 1: Unlinked and deleted shared memory\n");
	return 0;
}