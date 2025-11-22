// Reader’s code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO_NAME "/tmp/myfifo.txt"

int main()
{
    int fd, br;
    char buffer[100];

    // Create FIFO if it doesn't already exist
    if (mkfifo(FIFO_NAME, 0666) == -1)
    {
        if (errno != EEXIST)
        {
            perror("mkfifo error");
            return 1;
        }
    }

    printf("Reader: Waiting for writer to open the FIFO...\n");

    // Open FIFO for reading
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1)
    {
        perror("open for reading error");
        exit(1);
    }

    printf("Reader: Connection established. Reading data...\n");

    br = read(fd, buffer, sizeof(buffer) - 1);
    if (br > 0)
    {
        buffer[br] = '\0';
        printf("Reader: Message received (%d bytes):\n", br);
        printf(">> %s\n", buffer);
    }
    else if (br == 0)
    {
        printf("Reader: Writer closed the FIFO before sending data.\n");
    }
    else
    {
        perror("read error");
    }

    close(fd);
    return 0;
}
