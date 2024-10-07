#include <stdio.h>
#include <stdbool.h>

struct process_struct
{
    int at;
    int bt;
    int priority;
    int ct, wt, tat, rt, start_time;
} ps[100];

int main()
{
    int n;
    bool is_completed[100] = {false};
    int bt_remaining[100];
    int current_time = 0;
    int completed = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int total_idle_time = 0, prev = 0;

    printf("\nEnter the number of processes:");
    scanf("%d", &n);

    printf("\nEnter the arrival time of processes:");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].at);
    }

    printf("\nEnter the burst time of processes:");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].bt);
        bt_remaining[i] = ps[i].bt;
    }

    printf("\nEnter the priority of processes:");

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].priority);
    }

    while (completed != n)
    {
        int max_index = -1;
        int maximum = -1;

        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (ps[i].priority > maximum)
                {
                    maximum = ps[i].priority;
                    max_index = i;
                }
                else if (ps[i].priority == maximum)
                {
                    if (ps[i].at < ps[max_index].at)
                    {
                        max_index = i;
                    }
                }
            }
        }

        if (max_index == -1)
        {
            current_time++;
        }
        else
        {
            if (bt_remaining[max_index] == ps[max_index].bt)
            {
                ps[max_index].start_time = current_time;
                if (completed > 0)
                    total_idle_time += (ps[max_index].start_time - prev);
            }

            bt_remaining[max_index]--;
            current_time++;

            if (bt_remaining[max_index] == 0)
            {
                ps[max_index].ct = current_time;
                ps[max_index].tat = ps[max_index].ct - ps[max_index].at;
                ps[max_index].wt = ps[max_index].tat - ps[max_index].bt;
                ps[max_index].rt = ps[max_index].start_time - ps[max_index].at;

                sum_tat += ps[max_index].tat;
                sum_wt += ps[max_index].wt;
                sum_rt += ps[max_index].rt;

                completed++;
                is_completed[max_index] = true;

                prev = current_time;
            }
        }
    }

    int max_completion_time = ps[0].ct, min_arrival_time = ps[0].at;
    for (int i = 1; i < n; i++)
    {
        if (ps[i].ct > max_completion_time)
            max_completion_time = ps[i].ct;
        if (ps[i].at < min_arrival_time)
            min_arrival_time = ps[i].at;
    }
    int length_cycle = max_completion_time - min_arrival_time;

    float throughput = (float)n / length_cycle;
    float cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle * 100;

    printf("\nProcess\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, ps[i].at, ps[i].bt, ps[i].start_time, ps[i].ct,
               ps[i].tat, ps[i].wt, ps[i].rt);
    }

    printf("\nAverage Turnaround Time: %.2f", sum_tat / n);
    printf("\nAverage Waiting Time: %.2f", sum_wt / n);
    printf("\nAverage Response Time: %.2f", sum_rt / n);
    printf("\nThroughput: %.2f", throughput);
    printf("\nCPU Utilization: %.2f%%\n", cpu_utilization);

    return 0;
}
