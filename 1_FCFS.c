#include <stdio.h>
#include <stdlib.h>

struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    float tat;
    float wt;
    int rt;
    int st;
};

int compare(const void *p1, const void *p2)
{
    int a = ((struct Process *)p1)->at;
    int b = ((struct Process *)p2)->at;
    return (a < b) ? -1 : 1;
}

int main()
{
    int n, swt = 0, stat = 0, sbt = 0, srt = 0;
    float awt, atat, cpu_utilization, throughput;

    printf("\nEnter the number of processes.");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter the value of  arrival time and burst time for process %d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    qsort((void *)p, n, sizeof(struct Process), compare);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            p[i].ct = p[i].at + p[i].bt;
        }
        else if (p[i - 1].ct <= p[i].at)
        {
            p[i].ct = p[i].at + p[i].bt;
        }
        else
        {
            p[i].ct = p[i - 1].ct + p[i].bt;
        }

        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        sbt += p[i].bt;
        swt += p[i].wt;
        stat += p[i].tat;
        p[i].rt = p[i].wt;
    }

    awt = swt / n;
    atat = stat / n;

    float max = 0;
    for (int i = 0; i < n; i++)
    {
        p[i].st = p[i].rt + p[i].at;
        if (p[i].ct > max)
        {
            max = p[i].ct;
        }
    }

    cpu_utilization = (sbt / max) * 100;
    throughput = n / max;

    printf("\nProcess ID\tAriival Time\tBurst Time\tStart Time\tCompletion Time\t  Turn Around Time\tWaiting Time\t   Response Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("  P%d\t\t  %d\t\t  %d\t\t  %d\t\t  %d\t\t    %f\t\t  %f\t\t  %d\n", p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nSum of Turn Around Time: %d\nAverage of Turn Around Time: %f", stat, atat);
    printf("\nSum of Waiting Time: %d\nAverage of Waiting Time: %f", swt, awt);
    printf("\nCPU Utilization is: %f", cpu_utilization);
    printf("\nThroughput is: %f", throughput);

    return 0;
}
