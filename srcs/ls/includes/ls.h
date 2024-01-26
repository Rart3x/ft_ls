#pragma once

#include "../../libft/include/libft.h"

#include "enum.h"
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

typedef struct t_arr { 
    char *str;

    unsigned char type;

}   s_arr;

typedef struct t_args {
    char **arr;

}   s_args;

typedef struct t_dirs {
    s_arr   *arr;
    char    *directory;

    size_t capacity;
    size_t size;

    struct t_dirs *next;

}   s_dirs;

typedef struct t_flags {
    bool a;
    bool l;
    bool r;
    bool R;
    bool t;

}   s_flags;

typedef struct t_vars {
    s_args  args;
    s_dirs  dirs;
    s_flags flags;

}   s_vars;

char    **init_args(char **args, int ac, char **av);
s_dirs  *init_dirs(const char *directory);

void    init_struc_arr(s_arr *arr);
void    init_struc_args(s_args *args);
void    init_struc_dirs(s_dirs *dirs);
void    init_struc_flags(s_flags *flags);
void    init_structs(s_vars *vars);


void    without_args(s_vars *vars);
// void    with_args(s_vars *vars);

void free_dirs(s_dirs *dirs);