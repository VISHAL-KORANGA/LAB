#include <stdio.h>
#include <unistd.h>
int main()
{
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("Child 1: Listing files in the current directory:\n");
        execlp("ls", "ls", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("Child 2: Sleeping for 5 seconds...\n");
            sleep(5);
            printf("Child 2: Done sleeping!\n");
            exit(0);
        }
        else if (pid2 > 0)
        {
            printf("\n\n\nParent: Waiting for Child 1 to finish...\n");
            waitpid(pid1, NULL, 0);
            printf("Parent: Child 1 has completed.\n");
            printf("Parent: Waiting for Child 2 to finish...\n");
            waitpid(pid2, NULL, 0);
            printf("Parent: Child 2 has completed.\n");
        }
    }
    else
    {
        perror("fork");
    }
}