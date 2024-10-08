// Q2. Write a program to print process Id's of parent and child process i.e. parent should print
// its own and its child process id while child process should print its own and its parent process
// id. (use getpid(), getppid()).
// SOURCE CODE:
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    int pid = fork();
    if (pid == 0)
    {
        printf("\n\n\nChild Process");
        printf("\nProcess id of child process:%d", getpid());
        printf("\nParent process id:%d", getppid());
    }

    else if (pid < 0)
    {
        printf("\nchild process not created");
    }
    else
    {
        printf("\n\n\nParent Process");
        printf("\nProcess id of parent process:%d", getpid());
        printf("\nchild process id:%d", pid);
    }
    return 0;
}
