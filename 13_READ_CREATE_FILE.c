#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
void writeToFile(char *filename, char *content)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return;
    }
    write(fd, content, strlen(content));
    close(fd);
}
void printMatchingLines(char *file1, char *file2)
{
    FILE *fp1 = fopen(file1, "r");
    FILE *fp2 = fopen(file2, "r");
    if (!fp1 || !fp2)
    {
        perror("fopen");
        if (fp1)
            fclose(fp1);
        if (fp2)
            fclose(fp2);
        return;
    }
    char line1[256], line2[256];
    while (fgets(line1, sizeof(line1), fp1) != NULL)
    {
        rewind(fp2);
        while (fgets(line2, sizeof(line2), fp2) != NULL)
        {
            if (strcmp(line1, line2) == 0)
            {
                printf("Matching line: %s", line1);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
}
int main()
{
    char myDetails[] = "Name: Anchal Panwar\nAge: 19\nDepartment: CSE\n";
    char friendDetails[] = "Name: Prerna Rawat\nAge: 19\nDepartment: CSE\n";
    writeToFile("mydetails.txt", myDetails);
    writeToFile("frienddetails.txt", friendDetails);
    printf("\nMatching lines in both files:\n");
    printMatchingLines("mydetails.txt", "frienddetails.txt");
    return 0;
}