#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
	int fd = open("data.txt", O_RDWR);
	if (fd == -1)
	{
		perror("file ka masla");
		exit(1);
	}

	// Get file size
	size_t file_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	// Map the file into memory using mmap
	char *mapped_mem = mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mapped_mem == MAP_FAILED)
	{
		perror("mmap");
		exit(1);
	}

	// Step 3: Display the content of the mapped memory region
	printf("Original content:\n");
	printf("%.*s\n", (int) file_size, mapped_mem);

	const char *append_text = " - Updated!";
	strcpy(mapped_mem + file_size, append_text);

	printf("\nUpdated content:\n");
	printf("%s\n", mapped_mem);

	munmap(mapped_mem, file_size);
	close(fd);

	printf("\nMemory unmapped and file closed successfully.\n");

	return 0;
}
