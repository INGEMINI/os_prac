#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // Error
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("Hello from Child! PID: %d, Parent PID: %d\n", getpid(), getppid());
    }
    else
    {
        // Parent process
        printf("Hello from Parent! PID: %d, Child PID: %d\n", getpid(), pid);
    }

    return 0;
}
