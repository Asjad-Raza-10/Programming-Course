#include "shared_Q4.h"

int main()
{
	int shm_fd = shm_open(SHM_NAME, O_RDONLY, 0666);
	if (shm_fd == -1)
	{
		perror("shm_open");
		exit(1);
	}

	struct shared_data *data = mmap(NULL, sizeof(struct shared_data), PROT_READ, MAP_SHARED, shm_fd, 0);
	if (data == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}

	while (data->done == 0)
	{
		printf("Consumer: counter = %d\n", data->counter);
		sleep(1);
	}

	printf("Final counter value: %d\n", data->counter);

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

	if (shm_unlink(SHM_NAME) == -1)
	{
		perror("shm_unlink");
		exit(1);
	}

	return 0;
}