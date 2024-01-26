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

s_dirs* init_dirs(const char *directory) {
    s_dirs *dirs = malloc(sizeof(s_dirs));
    if (dirs != NULL) {
        dirs->arr = malloc(sizeof(s_arr));
        if (dirs->arr != NULL) {
            dirs->size = 0;
            dirs->capacity = 1;
            dirs->directory = strdup(directory);
            dirs->next = NULL;
        } else {
            free(dirs);
            dirs = NULL;
        }
    }
    return dirs;
}

void    init_structs(s_vars *vars) {
    init_struc_args(&vars->args);
    init_struc_dirs(&vars->dirs);
    init_struc_flags(&vars->flags);
    init_struc_arr(vars->dirs.arr);
}

void    init_struc_arr(s_arr *arr) {
    arr->str = NULL;
    arr->type = 0;
}

void    init_struc_args(s_args *args) { 
    args->arr = NULL;
}

void    init_struc_dirs(s_dirs *dirs) {
    dirs->arr = malloc(sizeof(s_arr));
    dirs->directory = NULL;
}

void    init_struc_list(t_list *list) {
    list->content = NULL;
    list->next = NULL;
}


void    init_struc_flags(s_flags *flags) { 
    flags->a = false;
    flags->l = false;
    flags->r = false;
    flags->R = false;
    flags->t = false;
}