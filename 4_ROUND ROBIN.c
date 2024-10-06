#include <stdio.h>

struct Process
{
    int id;              // Process ID
    int arrival_time;    // Arrival time of the process
    int burst_time;      // Burst time of the process
    int remaining_time;  // Remaining time of the process
    int waiting_time;    // Waiting time of the process
    int turnaround_time; // Turnaround time of the process
};

// Function to calculate waiting times for all processes
void find_waiting_time(struct Process proc[], int n, int quantum)
{
    int remaining_processes = n; // Count of remaining processes
    int time = 0;                // Current time

    // Loop until all processes are completed
    while (remaining_processes > 0)
    {
        int done = 1; // Flag to check if all processes are done

        // Iterate through all processes
        for (int i = 0; i < n; i++)
        {
            // If the process has remaining time and has arrived
            if (proc[i].remaining_time > 0 && proc[i].arrival_time <= time)
            {
                done = 0; // There is at least one process that is not done

                // If remaining time is greater than quantum
                if (proc[i].remaining_time > quantum)
                {
                    time += quantum;                   // Increment time by quantum
                    proc[i].remaining_time -= quantum; // Reduce remaining time
                }
                else
                {
                    // If remaining time is less than or equal to quantum
                    time += proc[i].remaining_time;                                          // Increment time by remaining time
                    proc[i].waiting_time = time - proc[i].arrival_time - proc[i].burst_time; // Calculate waiting time
                    proc[i].turnaround_time = time - proc[i].arrival_time;                   // Calculate turnaround time
                    proc[i].remaining_time = 0;                                              // Mark process as completed
                    remaining_processes--;                                                   // Decrement remaining processes count
                }
            }
        }

        // If no process was executed in this iteration, increment time
        if (done)
        {
            time++;
        }
    }
}

// Function to calculate turnaround times for all processes
void find_turnaround_time(struct Process proc[], int n)
{
    for (int i = 0; i < n; i++)
    {
        // Turnaround time is waiting time plus burst time
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
    }
}

// Function to print the average waiting and turnaround times
void print_average_times(struct Process proc[], int n)
{
    float total_waiting_time = 0, total_turnaround_time = 0;

    // Print the details of each process
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time);
        // Accumulate total waiting and turnaround times
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    // Calculate and print average waiting and turnaround times
    printf("\nAverage Waiting Time: %.2f", total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround_time / n);
}

int main()
{
    int n;                    // Number of processes
    int quantum;              // Time quantum for Round Robin scheduling
    struct Process proc[100]; // Array to hold process information (max 100 processes)

    // Prompt user for the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Loop to get arrival and burst times for each process
    for (int i = 0; i < n; i++)
    {
        proc[i].id = i + 1; // Assign process ID
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
        proc[i].remaining_time = proc[i].burst_time; // Initialize remaining time
    }

    // Prompt user for the time quantum
    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    // Calculate waiting times
    find_waiting_time(proc, n, quantum);
    // Calculate turnaround times
    find_turnaround_time(proc, n);
    // Print the average times
    print_average_times(proc, n);

    return 0; // End of program
}
