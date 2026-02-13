#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t p1 = fork();
    
    if(p1 < 0)
    {
        // Error forking
        perror("First fork failed");
        exit(EXIT_FAILURE);
    }
    else if(p1 > 0)
    {
        // Parent process
        
        // Creating second child
        pid_t p2 = fork();

        if(p2 < 0)
        {
            // Error forking
            perror("Second fork failed");
            exit(EXIT_FAILURE);
        }
        else if(p2 > 0)
        {
            // Parent process

            // Creating third child
            pid_t p3 = fork();

            if(p3 < 0)
            {
                // Error forking
                perror("Second fork failed");
                exit(EXIT_FAILURE);
            }
            else if(p3 > 0)
            {
                // Parent process

                wait(NULL);
            }
            else 
            {
                // Child process
                printf("This is the 3rd child. It will run date.\n");
                execlp("/usr/bin/date", "date", NULL);
            }

            wait(NULL);
        }
        else 
        {
            // Child process
            printf("This is the 2nd child. It will run rm garbage.txt.\n");
            execlp("/usr/bin/rm", "rm", "garbage.txt", NULL);
        }

        wait(NULL);
    }
    else 
    {
        // Child process
        printf("This is the 1st child. It will run pwd.\n");
        execlp("/usr/bin/pwd", "pwd",NULL);
    }
    

    return 0;
}