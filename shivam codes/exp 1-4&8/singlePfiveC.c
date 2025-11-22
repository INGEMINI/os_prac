#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    int i;

    for (i = 1; i <= 5; i++)
    {
        pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            return 1;
        }
        else if (pid == 0)
        {
            // Inside child
            printf("Child %d created with PID: %d, Parent PID: %d\n", i, getpid(), getppid());
            return 0; // Each child exits after printing
        }
        // Parent continues loop
    }

    // Optional: sleep to keep parent alive so children don't become orphans
    sleep(2);
    return 0;
}
