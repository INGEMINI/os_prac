// receiver.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    // Generate same key
    key = ftok("progfile", 65);
    printf("Unique key created using ftok: %d\n", key);

    // Access message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }
    printf("Message queue ID: %d\n", msgid);

    // Receive message
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Message received: %s\n", message.msg_text);
    printf("Message type: %ld\n", message.msg_type);
    printf("Size of message: %ld bytes\n", strlen(message.msg_text));

    // Remove message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl remove failed");
        exit(1);
    }

    printf("Message queue removed with ID: %d\n", msgid);
    printf("Status: Queue deletion successful\n");

    return 0;
}
