#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
            // This is the child of parent i
            printf("Child created by Parent %d - Child PID: %d, Parent PID: %d\n", i, getpid(), getppid());
            return 0;
        }
        else
        {
            // Parent waits for its child
            wait(NULL);
        }
    }

    return 0;
}
