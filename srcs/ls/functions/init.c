#include "../includes/ls.h"

/*---------------------------Random Init---------------------------*/
char    **init_args(char **arr, int ac, char **av) {
    
    arr = malloc(sizeof(char *) * (count_args_2d(av) - 1));
    if (!arr)
        return false;

    for (size_t i = 1; i < (size_t)ac; i++) {
        arr[i - 1] = ft_strdup(av[i]);
    }
    return arr;
}

void   init_dirs(s_dirs *dirs, const char *directory) {
    if (dirs != NULL) {
        dirs->arr = malloc(sizeof(s_arr));
        if (dirs->arr != NULL) {
            init_struc_arr(dirs->arr);
            dirs->size = 0;
            dirs->capacity = 1;
            dirs->directory = strdup(directory);
            dirs->next = NULL;
        } else {
            free(dirs);
            return;
        }
    }
}

/*---------------------------Structs Init---------------------------*/
void    init_structs(s_vars *vars) {
    vars->dirs = malloc(sizeof(s_dirs));
    if (!vars->dirs)
        exit(0);

    init_struc_dirs(vars->dirs);
    init_struc_flags(&vars->flags);
}

void    init_struc_arr(s_arr *arr) {
    arr->str = NULL;
    arr->type = 0;
    arr->executable = false;
    arr->readable = false;
    arr->writable = false;
}

void    init_struc_dirs(s_dirs *dirs) {
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