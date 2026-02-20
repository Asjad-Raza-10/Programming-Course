#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    
    if(pid == 0)
    {
        // child process
        execl("./even", "./even", NULL);
        perror("execl failed!");
        exit( EXIT_FAILURE );
    }
    else if(pid > 0)
    {
        // parent process
        wait(NULL);
    }
    else
    {
        perror("fork failed");
        exit( EXIT_FAILURE );
    }

    return 0;
}