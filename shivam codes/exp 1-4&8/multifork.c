#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Start of the program. PID: %d\n", getpid());

    fork(); // First fork
    fork(); // Second fork

    printf("Hello from process PID: %d\n", getpid());

    return 0;
}
