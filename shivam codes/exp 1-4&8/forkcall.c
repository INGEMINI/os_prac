#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // Error occurred
        perror("fork failed");
        return 1;
    }

    // Both parent and child will print
    printf("Hello World\n");

    return 0;
}
