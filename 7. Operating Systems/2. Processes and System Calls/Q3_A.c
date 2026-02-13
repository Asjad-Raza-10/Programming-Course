#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid = fork();
    
    if(pid < 0)
    {
        // Error forking
        perror("First fork failed");
        exit(EXIT_FAILURE);
    }
    else if(pid > 0)
    {
        // Parent process
        sleep(20);
        printf("Exitting from the parent process now.\n");
    }
    else 
    {
        // Child process
        printf("Child process running (PID = %d)\n", getpid());
        printf("Exitting from the child process now.\n");
        exit(0);
    }
    

    return 0;
}