#include "shared_Q4.h"

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		perror("Incorrect Input Bhaiii");
		exit(1);
	}

	int n = atoi(argv[1]); // Convert string to integer

	shm_unlink(SHM_NAME); // Remove any existing shared memory

	int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
	if (shm_fd == -1)
	{
		perror("shm_open");
		exit(1);
	}

	if (ftruncate(shm_fd, sizeof(struct shared_data)) == -1)
	{
		perror("ftruncate");
		exit(1);
	}

	struct shared_data *data = mmap(NULL, sizeof(struct shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (data == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}

	data->counter = 0;
	data->done = 0;

	for (int i = 0; i < n; i++)
	{
		data->counter++;
		printf("Producer: counter = %d\n", data->counter);
		sleep(1);
	}

	data->done = 1;

	if (munmap(data, sizeof(struct shared_data)) == -1)
	{
		perror("munmap");
		exit(1);
	}

	if (close(shm_fd) == -1)
	{
		perror("close");
		exit(1);
	}

	printf("Producer finished.\n");
	return 0;
}