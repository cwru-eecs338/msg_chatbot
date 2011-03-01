#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "common.h"
#include "responses.h"

void main_loop(int);
void interrupt_handler(int);
void respond(char*, struct chat_msg*);

int interrupted = 0;

int main() {
    // Setup signal handler
    assert(signal(SIGINT, interrupt_handler) != SIG_ERR);

    // Get key for message queue
    key_t msgkey = try(
        ftok("common.h", PROJ_ID),
        "Could not get message queue key."
    );

    // Create Queue with key
    int msgqid = try(
        msgget(msgkey, IPC_CREAT | 0600),
        "Could not create message queue"
    );

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

    // Seed random number generator
    srand(time(NULL));

    // Structures for holding messages
    struct chat_msg incoming, outgoing;
    outgoing.return_type = (long int) pid;

    // Function return status
    int status;

    while(!interrupted) {

        // Receive message
        status = msgrcv(
            msgqid,                  // Queue ID
            (void *) &incoming,      // Place to store it
            sizeof(struct chat_msg), // Maximum size
            (long int) pid,          // Message type (for us)
            0);                      // No flags
        // If we were interrupted or
        // or some error occurred
        if(status < 0) { break; }

        // Construct response
        outgoing.message_type = incoming.return_type;
        respond(incoming.buffer, &outgoing);

        // Send message
        status = msgsnd(
            msgqid,                  // Queue ID
            (void *) &outgoing,      // Message to send
            sizeof(struct chat_msg), // Message Size
            0);                      // No flags
        // If we were interrupted or
        // or some error occurred
        if(status < 0) { break; }

    }

    puts("Server shutting down...");
}

/*
 * Respond to the message, and place it
 * in the outgoing message structure.
 * TODO: Pass the Turing Test
 */
void respond(char* msg, struct chat_msg* outgoing) {
    const char **resp_pool;
    int pool_size;
    if(strchr(msg, '?') != NULL) {
        resp_pool = RESP_TO_QUESTION;
        pool_size = LENGTH(RESP_TO_QUESTION);
    } else if(strchr(msg, '!') != NULL) {
        resp_pool = RESP_TO_EXCL;
        pool_size = LENGTH(RESP_TO_EXCL);
    } else {
        resp_pool = RESP_DEFAULT;
        pool_size = LENGTH(RESP_DEFAULT);
    }
    const char *response = resp_pool[rand() % pool_size];
    strcpy(outgoing->buffer, response);
}

/*
 * Called to handle SIGINT
 */
void interrupt_handler(int sig) {
    interrupted = 1;
}
