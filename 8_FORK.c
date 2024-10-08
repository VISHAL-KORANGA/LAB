// Q1. Write a program to create a child process using system call fork().
// SOURCE CODE:
#include <stdio.h>
#include <unistd.h>
int main()
{
    int p = fork();
    printf("\nProcess Created");
    printf("\nProcess ID:%d", p);
    return 0;
}
