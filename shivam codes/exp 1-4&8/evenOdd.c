#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        // Fork failed
        perror("fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process: Sum of odd numbers
        int sum = 0;
        for (int i = 1; i <= 10; i++)
        {
            if (i % 2 != 0)
            {
                sum += i;
            }
        }
        printf("Child Process (PID: %d): Sum of odd numbers = %d\n", getpid(), sum);
    }
    else
    {
        // Parent process: Wait for child, then compute even sum
        wait(NULL); // Wait for child to finish
        int sum = 0;
        for (int i = 1; i <= 10; i++)
        {
            if (i % 2 == 0)
            {
                sum += i;
            }
        }
        printf("Parent Process (PID: %d): Sum of even numbers = %d\n", getpid(), sum);
    }

    return 0;
}
