#include <stdio.h>

// Define a structure for Process to store its details
struct Process
{
    int id;             // Process ID
    int arrivalTime;    // Arrival time of the process
    int burstTime;      // Burst time of the process
    int completionTime; // Completion time when the process finishes
    int waitingTime;    // Waiting time for the process
    int turnAroundTime; // Turnaround time for the process
    int isCompleted;    // Flag to check if the process is completed
};

// Function to execute SJF (non-preemptive) scheduling algorithm
void sjfScheduling(struct Process p[], int n)
{
    int totalTime = 0, completed = 0, shortest = 0;
    float avgWaitingTime = 0, avgTurnAroundTime = 0;

    // Initialize all processes as incomplete
    for (int i = 0; i < n; i++)
    {
        p[i].isCompleted = 0;
    }

    // Loop until all processes are completed
    while (completed != n)
    {
        int minBurstTime = 10000; // Minimum burst time to find the shortest job
        int isProcessSelected = 0;

        // Traverse all processes to find the process with shortest burst time that has arrived
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrivalTime <= totalTime && p[i].isCompleted == 0 && p[i].burstTime < minBurstTime)
            {
                minBurstTime = p[i].burstTime;
                shortest = i;
                isProcessSelected = 1; // A process has been selected
            }
        }

        // If no process is found, move to the next unit of time
        if (isProcessSelected == 0)
        {
            totalTime++;
            continue;
        }

        // Set completion time of the selected process
        totalTime += p[shortest].burstTime;
        p[shortest].completionTime = totalTime;

        // Calculate turnaround time and waiting time for the selected process
        p[shortest].turnAroundTime = p[shortest].completionTime - p[shortest].arrivalTime;
        p[shortest].waitingTime = p[shortest].turnAroundTime - p[shortest].burstTime;

        // Mark the process as completed
        p[shortest].isCompleted = 1;
        completed++; // Increment the count of completed processes

        // Add to total waiting and turnaround time
        avgWaitingTime += p[shortest].waitingTime;
        avgTurnAroundTime += p[shortest].turnAroundTime;
    }

    // Print the process details after completion
    printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arrivalTime, p[i].burstTime, p[i].completionTime, p[i].turnAroundTime, p[i].waitingTime);
    }

    // Calculate and print average waiting and turnaround times
    avgWaitingTime /= n;
    avgTurnAroundTime /= n;
    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f", avgTurnAroundTime);
}

int main()
{
    int n;

    // Ask the user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Create an array of Process structures
    struct Process p[n];

    // Input for Arrival and Burst times for each process
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1; // Assigning process ID (starting from 1)
        printf("Enter arrival time for process %d: ", p[i].id);
        scanf("%d", &p[i].arrivalTime);
        printf("Enter burst time for process %d: ", p[i].id);
        scanf("%d", &p[i].burstTime);
    }

    // Execute the SJF scheduling algorithm
    sjfScheduling(p, n);

    return 0;
}
