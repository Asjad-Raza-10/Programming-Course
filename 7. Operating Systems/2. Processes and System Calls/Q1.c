#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int counter = 10;

    pid_t pid = fork();

    if(pid < 0)
    {
        // Error forking
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
        // Parent process
        while(counter != 0)
        {
            printf("Parent's Counter: %d\n", counter);
            counter--;
        }

    }
    else
    {
        // Child process
        while(counter != 0)
        {
            printf("Child's Counter: %d\n", counter);
            counter--;
        }
    }
    return 0;
}