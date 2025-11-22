#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0)
    {
        // Parent process
        printf("Parent process sleeping, PID: %d\n", getpid());
        sleep(30);   // Sleep to keep the parent alive
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process exiting, PID: %d\n", getpid());
        exit(0);     // Exit immediately, creating a zombie
    }
    else
    {
        perror("fork");
    }

    return 0;
}
