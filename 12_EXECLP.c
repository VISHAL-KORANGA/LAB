// Q2. Write a program to show working of execlp() system call by executing ls command.
// SOURCE CODE:
#include <stdio.h>
#include <unistd.h>
int main()
{
    execlp("ls", "ls", NULL);
    perror("execlp");
    return 0;
}