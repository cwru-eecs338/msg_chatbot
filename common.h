#ifndef MSG_CHATBOT_COMMON
#define MSG_CHATBOT_COMMON

/*
 * Actual Message
 */
#define MAX_MSG_LEN 140
struct chat_msg {
    long int return_type;
    char buffer[MAX_MSG_LEN];
};

/*
 * Message Buffer
 */
struct msgbuf {
    long int message_type;
    struct chat_msg data;
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

/*
 * For colorful output
 */
enum ANSI_COLOR {
    ANSI_BLACK = 30,
    ANSI_RED,
    ANSI_GREEN,
    ANSI_YELLOW,
    ANSI_BLUE,
    ANSI_MAGENTA,
    ANSI_CYAN,
    ANSI_WHITE
};

#endif
