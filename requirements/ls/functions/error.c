#include "../includes/ls.h"

void    err_cannot_access(char *err_message) { 
    ENOENT(err_message);
}

void    err_invalid_option(char *err_message) {
    INVALID_OPTION(err_message[1]);
}