#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process (PID: %d) is running.\n", getpid());
        sleep(2); // Simulate work
        printf("Child process (PID: %d) finished.\n", getpid());
    }
    else
    {
        // Parent process
        printf("Parent (PID: %d) waiting for child (PID: %d)...\n", getpid(), pid);
        wait(NULL); // Waits for any child
        printf("Parent process (PID: %d) detected child finished.\n", getpid());
    }

    return 0;
}
