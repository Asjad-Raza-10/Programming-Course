#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();
    int stdout_fd = dup(1);

    if(pid == 0)
    {
        // child process
        int fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
        
        if(fd < 0)
        {
            perror("Error Opening File!");
            exit( EXIT_FAILURE );
        }
        
        dup2(fd, 1);
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        
        close(fd);
        //dup2(stdout_fd,1);
    }
    else if(pid > 0)
    {
        // parent process
        wait(NULL);
        char data[100];
        FILE* file = fopen("output.txt", "r"); 
        
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