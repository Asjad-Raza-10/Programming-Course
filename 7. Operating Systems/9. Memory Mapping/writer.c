#include "shared.h"

int main()
{
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

	data->number = 14;
	strcpy(data->text, "Hellllooooolooolololololoolooo");

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

	printf("Writer completed.\n");
	return 0;
}