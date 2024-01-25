#include "../includes/ls.h"

char    **init_args(char **arr, int ac, char **av) {
    
    arr = malloc(sizeof(char *) * (count_args_2d(av) - 1));
    if (!arr)
        return false;

    for (size_t i = 1; i < (size_t)ac; i++) {
        arr[i - 1] = ft_strdup(av[i]);
    }
    return arr;
}

void    init_structs(s_vars *vars) {
    init_struc_args(&vars->args);
    init_struc_dirs(&vars->dirs);
    init_struc_flags(&vars->flags);
}

void    init_struc_args(s_args *args) { 
    args->arr = NULL;
}

void    init_struc_dirs(s_dirs *dirs) {
    dirs->directorys = NULL;
    dirs->directory = NULL;
}

void    init_struc_flags(s_flags *flags) { 
    flags->a = false;
    flags->l = false;
    flags->r = false;
    flags->R = false;
    flags->t = false;
}