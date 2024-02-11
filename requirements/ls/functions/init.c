#include "../includes/ls.h"

/*---------------------------Random Init---------------------------*/
void    init_dirs_according_to_directorys(s_vars *vars, int ac, char **av, char *directory) {
    if (!is_there_directory(ac, av))
        init_dirs(vars->dirs, ".");
    else
        init_dirs(vars->dirs, directory);
}

void   init_dirs(s_dirs *dirs, const char *directory) {
    if (dirs != NULL) {
        if (!dirs->arr)
            dirs->arr = malloc(sizeof(s_arr));

        if (dirs->arr != NULL) {
            init_struc_arr(dirs->arr);
            dirs->blocks = 0;
            dirs->capacity = 1;
            dirs->next = NULL;
            dirs->size = 0;
            
            if (dirs->directory)
                free(dirs->directory);
            
            dirs->directory = strdup(directory);
        }
        else
        {
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
    
    vars->current_dir = 0;
    vars->nb_dir = 0;

    vars->dirs->arr = NULL;
    vars->dirs->next = NULL;

    init_struc_dirs(vars->dirs);
    init_struc_flags(&vars->flags);
}

void    init_struc_arr(s_arr *arr) {
    arr->group = NULL;
    arr->owner = NULL;
    arr->path = NULL;
    arr->str = NULL;

    arr->executable = false;
    arr->readable = false;
    arr->writable = false;

    arr->blocks = 0;
    arr->size = 0;
    arr->type = 0;
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