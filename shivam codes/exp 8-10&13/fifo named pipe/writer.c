#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_NAME "/tmp/myfifo"
// pipe name

int main()
{
    int fd, bw;

    // Create FIFO if it doesn't already exist
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        if (errno != EEXIST)
        // Ignore error if FIFO already exists
        {
            perror("mkfifo error");
            return 1;
        }
    }

    // Open FIFO for writing
    fd = open(FIFO_NAME, O_WRONLY);
    // O_WRONLY is for write only mode ..for this excute reader file first ..its compulsory
    if (fd == -1)
    {
        perror("open for writing error");
        return 1;
    }

    const char *msg = "Hello from writer!\n";

    bw = write(fd, msg, strlen(msg) + 1);
    printf("Writer: Message sent (%d bytes)\n", bw);

    close(fd);
    return 0;
}

// run method
//  # TERMINAL 1:
//  gcc reader.c -o reader
//  ./reader

// # TERMINAL 2:
// gcc writer.c -o writer
// ./writer
