#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;          // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
    int completion_time; // Completion time
    int remaining_time; // Remaining time (for preemptive SJF)
    int is_completed;  // Flag to check if process is completed
};

// To store Gantt chart timeline (for preemptive)
int timeline[1000];  
int timeline_size = 0;

// Function to sort processes by arrival time
void sortByArrival(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Non-preemptive SJF implementation
void sjfNonPreemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    
    while (completed != n) {
        int idx = -1;
        int min_burst = INT_MAX;
        
        // Find process with minimum burst time that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            // Execute the process
            processes[idx].waiting_time = current_time - processes[idx].arrival_time;
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].is_completed = 1;
            
            current_time = processes[idx].completion_time;
            completed++;
        } else {
            current_time++;
        }
    }
}

// Preemptive SJF (Shortest Remaining Time First) implementation with Gantt chart
void sjfPreemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;

    timeline_size = 0; // reset

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = 0;
    }
    
    while (completed != n) {
        int idx = -1;
        int min_remaining = INT_MAX;
        
        // Find process with minimum remaining time that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].remaining_time < min_remaining) {
                    min_remaining = processes[i].remaining_time;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            // Record which process runs
            timeline[timeline_size++] = processes[idx].pid;

            // Execute the process for 1 unit of time
            processes[idx].remaining_time--;
            current_time++;
            
            // If process is completed
            if (processes[idx].remaining_time == 0) {
                processes[idx].completion_time = current_time;
                processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
                processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
                processes[idx].is_completed = 1;
                completed++;
            }
        } else {
            timeline[timeline_size++] = -1; // idle
            current_time++;
        }
    }
}

void printTable(struct Process processes[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    printf("--------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time,
               processes[i].completion_time);
    }
}

void printAverages(struct Process processes[], int n) {
    float total_waiting = 0, total_turnaround = 0;
    
    for (int i = 0; i < n; i++) {
        total_waiting += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
    }
    
    printf("\nAverage Waiting Time: %.2f\n", total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround / n);
}

void printGanttChart(struct Process processes[], int n, int is_preemptive) {
    printf("\nGantt Chart:\n");
    printf("-----------\n");

    if (is_preemptive) {
        // Print top bar
        for (int i = 0; i < timeline_size; i++) printf("----");
        printf("-\n");

        // Print process execution
        printf("|");
        for (int i = 0; i < timeline_size; i++) {
            if (timeline[i] == -1)
                printf("ID |"); // idle
            else
                printf("P%-2d|", timeline[i]);
        }
        printf("\n");

        // Print bottom bar
        for (int i = 0; i < timeline_size; i++) printf("----");
        printf("-\n");

        // Print time units
        printf("0");
        for (int i = 1; i <= timeline_size; i++) {
            printf("%4d", i);
        }
        printf("\n");
    } else {
        // For non-preemptive SJF
        for (int i = 0; i < n; i++) {
            printf("-----------");
        }
        printf("-\n");
        
        printf("|");
        for (int i = 0; i < n; i++) {
            printf("    P%d    |", processes[i].pid);
        }
        printf("\n");
        
        for (int i = 0; i < n; i++) {
            printf("-----------");
        }
        printf("-\n");
        
        printf("0");
        for (int i = 0; i < n; i++) {
            printf("         %d", processes[i].completion_time);
        }
        printf("\n");
    }
}

int main() {
    int n, choice;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter arrival time for process P%d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process P%d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].is_completed = 0;
    }
    
    printf("\nSelect SJF type:\n");
    printf("1. Non-preemptive SJF\n");
    printf("2. Preemptive SJF (Shortest Remaining Time First)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    // Sort processes by arrival time
    sortByArrival(processes, n);
    
    if (choice == 1) {
        sjfNonPreemptive(processes, n);
    } else if (choice == 2) {
        sjfPreemptive(processes, n);
    } else {
        printf("Invalid choice! Using non-preemptive SJF by default.\n");
        sjfNonPreemptive(processes, n);
    }
    
    // Print results
    printTable(processes, n);
    printAverages(processes, n);
    printGanttChart(processes, n, choice == 2);
    
    return 0;
}
