#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

const char *EXIT = "exit\n";
const char *PROMPT = "YOU: ";

void main_loop(int, int);

int main(int argc, char *argv[]) {
    // Check arguments
    if(argc != 2) {
        puts("Usage: ./client.o server_pid");
        return EXIT_SUCCESS;
    }

    // Parse arguments
    int server_pid = atoi(argv[1]);

    // Get key for message queue
    key_t msgkey = try(
        ftok("common.h", PROJ_ID),
        "Could not get message queue key."
    );

    // Open message queue
    int msgqid = try(
        msgget(msgkey, 0600),
        "Could not open message queue"
    );

    main_loop(msgqid, server_pid);

    return EXIT_SUCCESS;
}

void main_loop(int msgqid, int server_pid) {
    pid_t pid = getpid();

    // Structures for holding messages
    struct msgbuf incoming, outgoing;
    outgoing.message_type = (long int) server_pid;
    outgoing.data.return_type = (long int) pid;

    // Function return status
    int status;

    while(1) {

        // Prompt user for message
        printf("%s", PROMPT);
        fflush(stdout);
        do {
            fgets(outgoing.data.buffer, MAX_MSG_LEN, stdin);

            // If it's bigger than MAX_MSG_LEN,
            // keep reading it in until we hit
            // the newline character
        } while(strchr(outgoing.data.buffer, '\n') == NULL);

        // Check for exit command
        if(strcmp(outgoing.data.buffer, EXIT) == 0) {
            break;
        }

        // Send message
        status = msgsnd(
            msgqid,                  // Queue ID
            (void *) &outgoing,      // Message to send
            sizeof(struct chat_msg), // Message Size
            0);                      // No flags
        // If we were interrupted or
        // or some error occurred
        if(status < 0) { break; }

        // Receive response message
        status = msgrcv(
            msgqid,                  // Queue ID
            (void *) &incoming,      // Place to store it
            sizeof(struct chat_msg), // Maximum size
            (long int) pid,          // Message type (for us)
            0);                      // No flags
        // If we were interrupted or
        // or some error occurred
        if(status < 0) { break; }

        // Print server's message
        printf("\033[0;%dm", ANSI_GREEN);
        printf("SERVER: %s\033[0m\n", incoming.data.buffer);

    }
}
