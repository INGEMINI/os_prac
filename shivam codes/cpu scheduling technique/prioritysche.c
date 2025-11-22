#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Process {
    int pid;            // Process ID
    int arrival_time;   // Arrival time
    int burst_time;     // Burst time
    int priority;       // Priority (lower number = higher priority)
    int waiting_time;   // Waiting time
    int turnaround_time;// Turnaround time
    int completion_time;// Completion time
    int remaining_time; // Remaining time (for preemptive)
    int is_completed;   // Completion flag
};

// Global Gantt chart timeline
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

// Non-preemptive Priority Scheduling implementation
void priorityNonPreemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    timeline_size = 0;

    while (completed != n) {
        int idx = -1;
        int highest_priority = INT_MAX;
        
        // Find process with highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            // Record process in timeline (full burst time block)
            for (int t = 0; t < processes[idx].burst_time; t++) {
                timeline[timeline_size++] = processes[idx].pid;
            }

            // Execute the process
            processes[idx].waiting_time = current_time - processes[idx].arrival_time;
            processes[idx].completion_time = current_time + processes[idx].burst_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].is_completed = 1;
            
            current_time = processes[idx].completion_time;
            completed++;
        } else {
            timeline[timeline_size++] = -1; // idle
            current_time++;
        }
    }
}

// Preemptive Priority Scheduling implementation
void priorityPreemptive(struct Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    timeline_size = 0;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].is_completed = 0;
    }
    
    while (completed != n) {
        int idx = -1;
        int highest_priority = INT_MAX;
        
        // Find process with highest priority that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].is_completed) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
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
    printf("\nProcess ID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tCompletion Time\n");
    printf("----------------------------------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time,
               processes[i].priority,
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

void printGanttChart(int is_preemptive) {
    printf("\nGantt Chart:\n");
    printf("-----------\n");

    // Top bar
    for (int i = 0; i < timeline_size; i++) printf("----");
    printf("-\n");

    // Print processes
    printf("|");
    for (int i = 0; i < timeline_size; i++) {
        if (timeline[i] == -1)
            printf("ID |"); // Idle
        else
            printf("P%-2d|", timeline[i]);
    }
    printf("\n");

    // Bottom bar
    for (int i = 0; i < timeline_size; i++) printf("----");
    printf("-\n");

    // Time values
    printf("0");
    for (int i = 1; i <= timeline_size; i++) {
        printf("%4d", i);
    }
    printf("\n");
}

int main() {
    int n, choice;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    struct Process processes[n];
    
    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter details for process P%d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority (lower number = higher priority): ");
        scanf("%d", &processes[i].priority);
        processes[i].is_completed = 0;
    }
    
    printf("\nSelect Priority Scheduling type:\n");
    printf("1. Non-preemptive Priority Scheduling\n");
    printf("2. Preemptive Priority Scheduling\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    // Sort processes by arrival time
    sortByArrival(processes, n);
    
    if (choice == 1) {
        priorityNonPreemptive(processes, n);
    } else if (choice == 2) {
        priorityPreemptive(processes, n);
    } else {
        printf("Invalid choice! Using non-preemptive Priority Scheduling by default.\n");
        priorityNonPreemptive(processes, n);
    }
    
    // Print results
    printTable(processes, n);
    printAverages(processes, n);
    printGanttChart(choice == 2);
    
    return 0;
}
