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

int try(int, char*);

#endif
