#include <stdio.h>   // Standard input-output header
#include <stdbool.h> // To use the boolean data type

// Define a structure to store information about each process.
struct process_info
{
    int max[10];       // Maximum resources the process may need
    int allocated[10]; // Currently allocated resources to the process
    int need[10];      // Remaining resources that the process needs (max - allocated)
};

// Declare variables to store the number of processes and number of resources.
int no_of_process, no_of_resources;

// Function to take input from the user for processes and available resources.
void input(struct process_info process[no_of_process], int available[no_of_resources])
{
    // Loop through each process to gather information.
    for (int i = 0; i < no_of_process; i++)
    {
        printf("Enter process[%d] info\n", i); // Display process number
        printf("Enter Maximum Need: ");        // Ask for the maximum need of each resource
        for (int j = 0; j < no_of_resources; j++)
            scanf("%d", &process[i].max[j]); // Input max resource requirement for each resource

        printf("Enter No. of Allocated Resources for this process: "); // Input currently allocated resources
        for (int j = 0; j < no_of_resources; j++)
        {
            scanf("%d", &process[i].allocated[j]);                            // Input allocated resource for each resource
            process[i].need[j] = process[i].max[j] - process[i].allocated[j]; // Calculate and store the need for each resource
        }
    }

    // Input the available resources in the system.
    for (int i = 0; i < no_of_resources; i++)
    {
        scanf("%d", &available[i]); // Input available resources for each resource type
    }
}

// Function to display process information in a tabular format.
void showTheInfo(struct process_info process[no_of_process])
{
    printf("\nPID\tMaximum\t\tAllocated\tNeed\n"); // Print headers for the table
    for (int i = 0; i < no_of_process; i++)
    {
        printf("P[%d]\t", i); // Display process ID

        // Print max resources for the process.
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].max[j]);
        printf("\t\t");

        // Print allocated resources.
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].allocated[j]);
        printf("\t\t");

        // Print the remaining needed resources.
        for (int j = 0; j < no_of_resources; j++)
            printf("%d ", process[i].need[j]);
        printf("\n");
    }
}

// Function to apply the Banker's safety algorithm to check for a safe sequence.
bool applySafetyAlgo(struct process_info process[no_of_process], int available[no_of_resources], int safeSequence[no_of_process])
{
    bool finish[no_of_process]; // Track whether each process is finished
    int work[no_of_resources];  // Work array to temporarily store available resources

    // Initialize work array with available resources.
    for (int i = 0; i < no_of_resources; i++)
    {
        work[i] = available[i];
    }

    // Initially mark all processes as unfinished.
    for (int i = 0; i < no_of_process; i++)
        finish[i] = false;

    bool proceed = true; // Flag to indicate whether we found a process that can proceed
    int k = 0;           // Index to track the safe sequence

    // Loop until no more processes can proceed.
    while (proceed)
    {
        proceed = false; // Reset proceed flag

        // Loop through each process.
        for (int i = 0; i < no_of_process; i++)
        {
            bool flag = true; // Assume the process can proceed

            // Check if the process has not yet finished.
            if (finish[i] == false)
            {
                // Compare the process's need with the work array.
                for (int j = 0; j < no_of_resources; j++)
                {
                    // If the needed resource is greater than available, the process cannot proceed.
                    if (process[i].need[j] > work[j])
                    {
                        flag = false; // Process can't proceed
                        break;        // No need to check further resources
                    }
                }

                // If the process can proceed (flag is true).
                if (flag == true)
                {
                    // Update work array by adding allocated resources of this process.
                    for (int j = 0; j < no_of_resources; j++)
                        work[j] += process[i].allocated[j];

                    finish[i] = true;      // Mark this process as finished
                    safeSequence[k++] = i; // Add process to safe sequence
                    proceed = true;        // Set proceed flag to true, indicating we found a process to proceed
                }
            }
        }
    }

    // Check if all processes are finished.
    int i; // Declare i outside of the loop
    for (i = 0; i < no_of_process && finish[i] == true; i++)
    {
        continue; // Loop checks whether all processes have finished
    }

    // If all processes are finished, return true (safe state).
    if (i == no_of_process)
        return true;
    else
        return false; // Otherwise, return false (unsafe state)
}

// Function to check if the system is in a safe state or not.
bool isSafeState(struct process_info process[no_of_process], int available[no_of_resources], int safeSequence[no_of_process])
{
    // Apply the safety algorithm and return the result.
    if (applySafetyAlgo(process, available, safeSequence) == true)
        return true;
    return false;
}

// Main function
int main()
{
    // Input number of processes and resources.
    printf("Enter No of Process\n");
    scanf("%d", &no_of_process);

    printf("Enter No of Resource Instances in system\n");
    scanf("%d", &no_of_resources);

    int available[no_of_resources];  // Array to store available resources
    int safeSequence[no_of_process]; // Array to store the safe sequence

    // Create an array of structures to store process information.
    struct process_info process[no_of_process];

    printf("****Enter details of processes****\n");
    input(process, available); // Call input function to get process details

    showTheInfo(process);

    // Check if the system is in a safe state.
    if (isSafeState(process, available, safeSequence))
    {
        printf("\nSystem is in SAFE State\n"); // If safe, print safe state message
        printf("Safe Sequence is: ");
        for (int i = 0; i < no_of_process; i++)
            printf("P[%d] ", safeSequence[i]); // Print the safe sequence
        printf("1\n");                         // Final output to indicate successful safe sequence
    }
    else
        printf("0\n"); // Unsafe state indication

    return 0; // End of program
}
