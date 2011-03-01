#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

void main_loop(int);
void interrupt_handler(int);

int interrupted = 0;

int main() {
    // Setup signal handler
    assert(signal(SIGINT, interrupt_handler) != SIG_ERR);

    // Create Queue
    int msgqid = try(
        msgget(IPC_PRIVATE, IPC_CREAT | 0600),
        "Could not create message queue");

    main_loop(msgqid);

    // Cleanup Queue
    try(
        msgctl(msgqid, IPC_RMID, NULL),
        "Could not remove message queue"
    );
    return EXIT_SUCCESS;
}

void main_loop(int msgqid) {
    pid_t pid = getpid();
    printf("Server started with:\n\tpid: %d\n\tqid: %d\n",
        pid, msgqid);

    struct chat_msg incoming, outgoing;
    int status;
    while(!interrupted) {

        // Receive message
        status = msgrcv(
            msgqid,                  // Queue ID
            (void *) &incoming,     // Place to store it
            sizeof(struct chat_msg), // Maximum size
            (long int) pid,          // Message type (for us)
            0);                      // No flags
        // If we were interrupted or
        // or some error occurred
        if(status < 0) { break; }

        // Construct response
        outgoing.message_type = incoming.return_type;
        outgoing.return_type = (long int) pid;
        strcpy(outgoing.buffer, "Fine.");

        // Send message
        status = msgsnd(
            msgqid,                 // Queue ID
            (void *) &outgoing,      // Message to send
            sizeof(struct chat_msg), // Message Size
            0);                      // No flags
        // If we were interrupted or
        // or some error occurred
        if(status < 0) { break; }

    }

    puts("Server shutting down...");
}

void interrupt_handler(int sig) {
    interrupted = 1;
}
