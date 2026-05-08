#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

#define FILE_SIZE 100

// Thread function to replace integers with spaces
void *replace_digits(void *arg)
{
	char *map = (char *) arg;

	// Process 50 bytes starting from the pointer passed
	for (int i = 0; i < 50; i++)
	{
		if (isdigit(map[i]))
		{
			map[i] = ' ';
		}
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	// Check command line argument
	if (argc != 2)
	{
		printf("Incorrect input bratherrr!\n");
		exit(1);
	}

	// Open the file
	int fd = open(argv[1], O_RDWR);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}

	// Map the file into memory
	char *map = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (map == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}

	printf("Original content:\n");
	printf("%.*s\n\n", FILE_SIZE, map);

	// Create two threads
	pthread_t thread1, thread2;

	// Thread 1: processes first 50 bytes (map pointer)
	pthread_create(&thread1, NULL, replace_digits, (void *) map);

	// Thread 2: processes second 50 bytes (map + 50)
	pthread_create(&thread2, NULL, replace_digits, (void *) (map + 50));

	// Wait for both threads to complete
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	printf("Content after replacing digits with spaces:\n");
	printf("%.*s\n", FILE_SIZE, map);

	// Cleanup
	munmap(map, FILE_SIZE);
	close(fd);

	return 0;
}
