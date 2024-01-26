#include "../includes/ls.h"

void    with_args(s_vars *vars, int ac, char **av) {
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
        else
        {
            DIR *dir = opendir(av[i]);
            if (dir == NULL)
                err_cannot_access(av[i]);
        }
    }
}

void    without_args(s_vars *vars) {
    DIR *dir = opendir(".");
    if (dir == NULL)
        return;

    init_dirs(vars->dirs, ".");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            if (!add_element(vars->dirs, entry->d_name, entry->d_type)) {
                free_dirs_wa(vars->dirs);
                closedir(dir);
                return;
            }
            define_file_permissions(&vars->dirs->arr[vars->dirs->size - 1]);
        }
    }
    closedir(dir);
    print_ls_wa(vars);
    free_dirs_wa(vars->dirs);
}

int main(int ac, char **av) {
    s_vars vars;

    (void)av;

    init_structs(&vars);

    if (ac == 1)
        without_args(&vars);
    else
        with_args(&vars, ac, av);

    return (0);
}