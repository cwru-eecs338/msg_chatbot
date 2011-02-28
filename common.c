#include <stdio.h>
#include <stdlib.h>

int try(int ret_val, char* msg) {
    if(ret_val < 0) {
        perror(msg);
        abort();
    }
    return ret_val;
}
