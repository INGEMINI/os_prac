// sender.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer
{
    long msg_type;
    char msg_text[100];
} message;

int main()
{
    key_t key;
    int msgid;

    // Generate unique key
    key = ftok("progfile", 65);
    printf("Unique key created using ftok: %d\n", key);

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget failed");
        exit(1);
    }
    printf("Message queue ID: %d\n", msgid);

    // Input message
    printf("Enter message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    message.msg_text[strcspn(message.msg_text, "\n")] = '\0';
    // string complement span
    //  👉 Find the FIRST position in the string where ANY character from another string appears.
    message.msg_type = 1;

    printf("Sending message...\n");
    printf("Message type: %ld\n", message.msg_type);
    printf("Size of message: %ld bytes\n", strlen(message.msg_text));

    // Send message
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1)
    {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent successfully!\n");

    return 0;
}

// You can send messages of type:

// 1 → normal message

// 2 → urgent message

// 3 → warning message

// 10 → system message

// 100 → secret message