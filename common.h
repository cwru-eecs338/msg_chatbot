#ifndef MSG_CHATBOT_COMMON
#define MSG_CHATBOT_COMMON

/*
 * Message Structure
 */
#define MAX_MSG_LEN 140
struct chat_msg {
    long int message_type;
    long int return_type;
    char buffer[MAX_MSG_LEN];
};

/*
 * Project ID for key
 * generation with ftok()
 */
#define PROJ_ID 1

/*
 * Check return status;
 * print message and abort
 * if status < 0
 */
int try(int, char*);

#endif
