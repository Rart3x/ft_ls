#pragma once

#include "../../libft/include/libft.h"

#include "errors.h"

#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <time.h>
#include <unistd.h>

typedef struct t_args {
    char **args;

}   s_args;


typedef struct t_flags {
    bool a;
    bool l;
    bool r;
    bool R;
    bool t;

}   s_flags;


typedef struct t_vars {
    s_args  args;
    s_flags flags;

}   s_vars;