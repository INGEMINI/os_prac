#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid, at, bt, wt, ct, tat;
};

int main()
{
    int n;
    printf("ENTER NO OF PROCESSES: ");
    scanf("%d", &n);
    struct process p[n];
    int current = 0;
    float avgwt = 0, avgtat = 0;

    // Input
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter the arrival and burst time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    // Scheduling
    for (int i = 0; i < n; i++)
    {
        if (current < p[i].at)
        {
            current = p[i].at; // CPU idle until process arrives
        }
        p[i].wt = current - p[i].at;  // Waiting time
        current += p[i].bt;           // Advance time
        p[i].ct = current;            // Completion time
        p[i].tat = p[i].ct - p[i].at; // Turnaround time
    }

    // Print results
    printf("\nPROCESS\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
        avgwt += p[i].wt;
        avgtat += p[i].tat;
    }

    // Print averages
    printf("\nAverage Waiting Time = %.2f", avgwt / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgtat / n);

    return 0;
}
