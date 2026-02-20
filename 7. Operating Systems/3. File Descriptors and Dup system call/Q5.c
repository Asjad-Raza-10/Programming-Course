#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    int stdout_fd = dup(1);
    int stdin_fd = dup(0);

    // child process
    char data[100];

    int readd = open("numbers.txt", O_RDONLY);
    if(!readd)
    {
        perror("Error Opening File!");
        exit( EXIT_FAILURE );
    }
    
    dup2(readd, 0);

    int sum = 0;
    int num = 0;

    while(scanf("%d", &num) == 1)
    {
        sum += num;   
    }
    
    close(readd);
    dup2(stdin_fd, 0);
    

    int writee = open("sum.txt", O_WRONLY | O_CREAT, 0644);
    dup2(writee, 1);
    
    printf("Sum: %d", sum);
    
    close(writee);
    //dup2(stdout_fd, 1);

    return 0;
}