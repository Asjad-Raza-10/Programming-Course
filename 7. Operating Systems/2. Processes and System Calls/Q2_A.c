#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t p1 = fork();
    pid_t p2 = fork();
    pid_t p3 = fork();

    printf("HI \n");

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}