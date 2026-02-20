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
        printf("I am Child 2.\nMy PID is: %d\n", getpid());
        printf("My Parent's PID is: %d\n", getppid());
    }
    else if(pid > 0)
    {
        wait(NULL);
        // parent process
        printf("I am Child 1.\nMy PID is: %d\n", getpid());
        printf("My Parent's PID is: %d\n", getppid());
        
        pid_t pid2 = fork();

        if(pid2 == 0)
        {
            // child process
            printf("I am Grand Child 1.\nMy PID is: %d\n", getpid());
            printf("My Parent's PID is: %d\n", getppid());
        }
        else if(pid2 > 0)
        {
            wait(NULL);
            // parent process
            printf("I am Grand Child 2.\nMy PID is: %d\n", getpid());
            printf("My Parent's PID is: %d\n", getppid());
            
            pid_t pid2 = fork();
        }
        else
        {
            perror("fork failed");
            exit( EXIT_FAILURE );
        }
    }
    else
    {
        perror("fork failed");
        exit( EXIT_FAILURE );
    }

    return 0;
}