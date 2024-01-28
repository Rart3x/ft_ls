#include "../includes/ls.h"

bool add_element(s_dirs *dirs, const char *str, unsigned char type) {
    if (dirs->size == dirs->capacity) {
        s_arr *new = realloc(dirs->arr, 2 * dirs->capacity * sizeof(s_arr));

        if (new == NULL)
            return FALSE;
        
        dirs->arr = new;
        dirs->capacity *= 2;
    }

    dirs->arr[dirs->size].str = ft_strdup(str);
    dirs->arr[dirs->size].type = type;
    dirs->size++;

    return TRUE;
}

void    define_directory_blocks(s_vars *vars) {
    struct stat file_stat;

    for (size_t i = 0; i < vars->dirs->size; i++) {
        stat(vars->dirs->arr[i].str, &file_stat);

        ft_printf("%s\n", vars->dirs->arr[i].str);
        ft_printf("%d\n", file_stat.st_blocks);
        
        vars->dirs->arr[i].blocks = file_stat.st_blocks;
        vars->dirs->blocks += vars->dirs->arr[i].blocks;
    }
}

void    define_errors(int ac, char **av) { 
    for (size_t i = 1; i < (size_t)ac; i++) {
        DIR *dir = opendir(av[i]);

        if (dir == NULL && av[i][0] != '-')
            err_cannot_access(av[i]);
    }
}

void    define_flags(s_vars *vars, int ac, char **av) {
    for (size_t i = 1; i < (size_t)ac; i++) {
        if (av[i][0] == '-') {
            for (size_t j = 0; j < ft_strlen(av[i]); j++) { 
                switch (av[i][j]) {
                    case 'a':
                        vars->flags.a = true;
                        break;
                    case 'l':
                        vars->flags.l = true;
                        break;
                    case 'r':
                        vars->flags.r = true;
                        break;
                    case 'R':
                        vars->flags.R = true;
                        break;
                    case 't':
                        vars->flags.t = true;
                        break;
                }
            }
        }
    }
}

void    define_file_permissions(s_arr *arr) {
    struct stat file_stat;

    stat(arr->str, &file_stat);

    arr->executable = (file_stat.st_mode & S_IXUSR) ? true : false;
    arr->readable = (file_stat.st_mode & S_IRUSR) ? true : false;
    arr->writable = (file_stat.st_mode & S_IWUSR) ? true : false;
}

bool    define_is_there_directory(int ac, char **av) {
    for (size_t i = 1; i < (size_t)ac; i++) {
        DIR *dir = opendir(av[i]);

        if (dir)
            return true;
    }
    return false;
}