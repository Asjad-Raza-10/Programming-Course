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
        FILE* file = fopen("file.txt", "w");
        
        if(!file)
        {
            perror("Error Opening File!");
            exit( EXIT_FAILURE );
        }
        
        fprintf(file, "Hellooooooo!\n");
        fprintf(file, "My name is Asjaddddd Razaaaaaa\n");
        fclose(file);
    }
    else if(pid > 0)
    {
        // parent process
        wait(NULL);
        char data[100];
        FILE* file = fopen("file.txt", "r"); 
        
        if(!file)
        {
            perror("Error Opening File!");
            exit( EXIT_FAILURE );
        }
        
        while(fgets(data, sizeof(data), file) != NULL)
        {
            printf("%s", data);
        }
        fclose(file);
    }
    else
    {
        perror("fork failed");
        exit( EXIT_FAILURE );
    }

    return 0;
}