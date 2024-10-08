// Q1.Write a program to open a directory and list its contents.(use opendir(), readdir(),
//                                                               closedir())
//     .SOURCE CODE :
#include <stdio.h>
#include <dirent.h>
int main()
{
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        printf("Contents of directory:\n");
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    else
    {
        perror("opendir");
    }
    return 0;
}
