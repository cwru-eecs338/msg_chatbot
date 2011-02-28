#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
#include <signal.h>

#include "common.h"

void main_loop(void);
void interrupt_handler(int);

int interrupted = 0;

int main() {
    // Setup signal handler
    assert(signal(SIGINT, interrupt_handler) != SIG_ERR);

    // Create Queue
    int msgqid = try(
        msgget(IPC_PRIVATE, IPC_CREAT | 0600),
        "Could not create message queue");

    main_loop();

    // Cleanup Queue
    try(
        msgctl(msgqid, IPC_RMID, NULL),
        "Could not remove message queue"
    );
    return EXIT_SUCCESS;
}

void main_loop() {
    while(!interrupted) {

    }
    puts("Server shutting down...");
}

void interrupt_handler(int sig) {
    interrupted = 1;
}
