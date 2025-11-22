#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent exiting, PID: %d\n", getpid());
        exit(0); // Exit immediately
    }
    else if (pid == 0)
    {
        // Child process
        sleep(10); // Sleep to allow parent to exit first
        printf("Child process, PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else
    {
        perror("fork");
    }

    return 0;
}
