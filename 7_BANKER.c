#include <stdio.h>
#include <stdbool.h>

struct process_info
{
    int max[10];
    int allocated[10];
    int need[10];
};

int no_of_process, no_of_resources;

void input(struct process_info process[], int available[])
{
    for (int i = 0; i < no_of_process; i++)
    {
        printf("Enter process[%d] info\n", i);
        printf("Enter Maximum Need: ");
        for (int j = 0; j < no_of_resources; j++)
            scanf("%d", &process[i].max[j]);

        printf("Enter No. of Allocated Resources for this process: ");
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &process[i].allocated[j]);
            process[i].need[j] = process[i].max[j] - process[i].allocated[j];
        }
    }

    printf("Enter Available Resources: ");
    for (int i = 0; i < no_of_resources; i++)
        scanf("%d", &available[i]);
}

void showInfo(struct process_info process[], int available[])
{
    printf("\nProcess Information:\n");
    printf("PID\tMaximum\t\tAllocated\tNeed\t\tAvailable\n");

    for (int i = 0; i < no_of_process; i++)
    {
        printf("P[%d]\t", i);

        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].max[j]);

        printf("\t\t");

        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].allocated[j]);

        printf("\t\t");

        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].need[j]);

        if (i == 0)
        {
            printf("\t\t");
            for (int j = 0; j < no_of_resources; j++)
                printf("%d ", available[j]);
        }

        printf("\n");
    }
}

bool applySafetyAlgo(struct process_info process[], int available[], int safeSequence[])
{
    bool finish[no_of_process];
    int work[no_of_resources];

    for (int i = 0; i < no_of_resources; i++)
        work[i] = available[i];

    for (int i = 0; i < no_of_process; i++)
        finish[i] = false;

    bool proceed = true;
    int k = 0;

    while (proceed)
    {
        proceed = false;
        for (int i = 0; i < no_of_process; i++)
        {
            bool flag = true;

            if (finish[i] == false)
            {
                for (int j = 0; j < no_of_resources; j++)
                {
                    if (process[i].need[j] > work[j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag == true)
                {
                    for (int j = 0; j < no_of_resources; j++)
                        work[j] = work[j] + process[i].allocated[j];

                    finish[i] = true;
                    safeSequence[k++] = i;
                    proceed = true;
                }
            }
        }
    }

    for (int i = 0; i < no_of_process; i++)
    {
        if (finish[i] == false)
            return false;
    }
    return true;
}

bool isSafeState(struct process_info process[], int available[], int safeSequence[])
{
    if (applySafetyAlgo(process, available, safeSequence))
        return true;
    return false;
}

int main()
{
    printf("Enter No of Processes\n");
    scanf("%d", &no_of_process);

    printf("Enter No of Resource Instances in system\n");
    scanf("%d", &no_of_resources);

    int available[no_of_resources];
    int safeSequence[no_of_process];

    struct process_info process[no_of_process];

    printf("****Enter details of processes****\n");
    input(process, available);

    showInfo(process, available);

    if (isSafeState(process, available, safeSequence))
    {
        printf("\nSystem is in SAFE State\n");
        printf("Safe Sequence is: ");
        for (int i = 0; i < no_of_process; i++)
            printf("P[%d] ", safeSequence[i]);
        printf("\n");
    }
    else
    {
        printf("System is NOT in a SAFE State\n");
    }

    return 0;
}
