#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/*

    Description:
    This program demonstrates how a parent process can communicate with its child
    process using a pipe. The parent writes a message into the pipe, and the child
    reads it.
*/

int main()
{

    int pipefd[2]; // pipefd[0] -> READ end, pipefd[1] -> WRITE end
    pid_t pid;
    char buffer[50]; // Buffer to store the data read by child

    // 1. Create the pipe
    if (pipe(pipefd) == -1)
    {
        perror("pipe"); // If pipe creation fails
        exit(EXIT_FAILURE);
    }

    // 2. Fork to create a child process
    pid = fork();

    if (pid < 0)
    { // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    // ------------------ PARENT PROCESS ------------------
    if (pid > 0)
    {
        printf("PARENT: I am the parent process (PID: %d)\n", getpid());

        // 3. Close unused READ end of the pipe
        close(pipefd[0]);

        // 4. Write message into the pipe
        const char *message = "Hello child, from your parent!";
        printf("PARENT: Writing message to pipe...\n");
        write(pipefd[1], message, 28); // Writing 28 bytes (length of the message)

        // 5. Close WRITE end -> signals EOF to child
        close(pipefd[1]);

        // Wait for the child process to finish
        wait(NULL);
        printf("PARENT: Child has terminated. Parent is exiting.\n");
    }

    // ------------------ CHILD PROCESS ------------------
    else
    { // pid == 0
        printf("CHILD: I am the child process (PID: %d)\n", getpid());

        // 3. Close unused WRITE end of the pipe
        close(pipefd[1]);

        // 4. Read message from pipe into buffer
        int bytes_read = read(pipefd[0], buffer, sizeof(buffer));
        buffer[bytes_read] = '\0'; // Null-terminate string

        printf("CHILD: Read %d bytes from pipe: \"%s\"\n", bytes_read, buffer);

        // 5. Close READ end
        close(pipefd[0]);

        // Child exits
        exit(EXIT_SUCCESS);
    }

    return 0;
}
