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
        wait(NULL);
    }
    else 
    {
        // Child process
        execlp("/usr/bin/cat", "cat", "file.txt",NULL);
    }
    

    return 0;
}