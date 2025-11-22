#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <sys/wait.h>

#include <sys/ipc.h>

int main()
{
    int shmid;
    char *shared_memory;
    // 1. Generate a UNIQUE KEY
    key_t key = ftok("/Users/apple/Desktop/Shivam_Aggarwal 62(B)/file.txt", 65);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }
    printf("Unique key created using ftok: %d\n", key);
    // 2. Create shared memory
    //  key → the locker number

    // 1024 → size in bytes (1 KB block)

    // 0666 → read + write permissions

    // IPC_CREAT → create if not already present
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }
    printf("Shared memory id after creation: %d\n", shmid);

    pid_t pid = fork();

    // Both process can access the same shared memory.
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child (PID: %d) writing data into shared memory.\n", getpid());
        shared_memory = (char *)shmat(shmid, NULL, 0);
        // NULL → Let the OS decide the address where shared memory should be mapped.

        // 0 → Read+Write access by default.
        if (shared_memory == (char *)-1)
        {
            perror("shmat");
            exit(1);
        }
        printf("Shared memory attached at address (shmaddr): %p\n", shared_memory);
        strcpy(shared_memory, "hello parent! this is child via shared memory.");
        printf("Child: data written successfully.\n");
        shmdt(shared_memory);
    }
    else
    {
        wait(NULL);

        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)-1)
        {
            perror("shmat");
            exit(1);
        }
        printf("Parent: reading data from shared memory...\n");
        printf("Parent: received message = \"%s\"\n", shared_memory);
        printf("Size: %lu bytes\n", strlen(shared_memory));

        // parent detaches
        shmdt(shared_memory);
        // delete shared memory block
        shmctl(shmid, IPC_RMID, NULL);
        printf("Shared memory id after detaching: %d\n", shmid);
    }
    return 0;
}
