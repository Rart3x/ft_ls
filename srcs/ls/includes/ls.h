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
    char **arr;

}   s_args;

typedef struct t_flags {
    bool a;
    bool l;
    bool r;
    bool R;
    bool t;

}   s_flags;

typedef struct t_dirs {
    char **directorys;
    char *directory;
    
    struct s_dirs *next;

}   s_dirs;


typedef struct t_vars {
    s_args  args;
    s_dirs  dirs;
    s_flags flags;

}   s_vars;

char    **init_args(char **args, int ac, char **av);

void    init_struc_args(s_args *args);
void    init_struc_dirs(s_dirs *dirs);
void    init_struc_flags(s_flags *flags);
void    init_structs(s_vars *vars);