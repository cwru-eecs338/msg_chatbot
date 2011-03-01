#ifndef MSG_CHATBOT_RESPONSES
#define MSG_CHATBOT_RESPONSES

const char *RESP_TO_QUESTION[] =
{
    "Fine.",
    "I don't know.",
    "Maybe.",
    "Sure.",
    "Hmm."
};

const char *RESP_TO_EXCL[] =
{
    "Cool.",
    "Wow."
};

const char *RESP_DEFAULT[] =
{
    "Okay.",
    "Fine.",
    "What?"
};

#define LENGTH(x) (sizeof(x)/sizeof(*x))

#endif
