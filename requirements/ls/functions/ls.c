#include "../includes/ls.h"

void    with_args(s_vars *vars, int ac, char **av) {
    bool tmp = false;
    DIR *dir;

    define_errors(ac, av);
    define_flags(vars, ac, av);
    define_nb_dir(vars, ac, av);

    for (size_t i = 1; i < (size_t)ac; i++) {
        
        if (!is_there_directory(ac, av))
            dir = opendir(".");
        else
            dir = opendir(av[i]);
        if (dir && (is_file_exist(av[i]) || is_flag(av[i])))
        {
            if (!is_there_directory(ac, av))
                init_dirs(vars->dirs, ".");
            else
                init_dirs(vars->dirs, av[i]);

            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                tmp = false;
                if (is_file_exist(av[i]) && !is_directory(av[i])) {
                    if (!add_element(vars->dirs, av[i], entry->d_type)) {
                        closedir(dir);
                        free_dirs(vars->dirs);
                        return;
                    }
                    define_file_settings(&vars->dirs->arr[vars->dirs->size - 1]);
                    print_ls(vars, TRUE);
                    tmp = true;
                    break;
                }
                else if (!vars->flags.a && entry->d_name[0] != '.') {
                    if (!add_element(vars->dirs, entry->d_name, entry->d_type)) {
                        closedir(dir);
                        free_dirs(vars->dirs);
                        return;
                    }
                    define_file_settings(&vars->dirs->arr[vars->dirs->size - 1]);
                }
                else if (vars->flags.a) {
                    if (!add_element(vars->dirs, entry->d_name, entry->d_type)) {
                        closedir(dir);
                        free_dirs(vars->dirs);
                        return;
                    }
                    define_file_settings(&vars->dirs->arr[vars->dirs->size - 1]);
                }
            }
            if (!tmp) {
                if (!vars->flags.l)
                    print_ls(vars, FALSE);
                else
                    print_ls_long_format(vars);
            }
        }
        closedir(dir);
        free_dirs(vars->dirs);
    }
    free(vars->dirs);
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
                closedir(dir);
                free_dirs(vars->dirs);
                return;
            }
            define_file_settings(&vars->dirs->arr[vars->dirs->size - 1]);
        }
    }
    print_ls(vars, FALSE);

    closedir(dir);
    free_dirs(vars->dirs);
}

int main(int ac, char **av) {
    s_vars vars;

    init_structs(&vars);

    if (ac == 1)
        without_args(&vars);
    else
        with_args(&vars, ac, av);

    return (0);
}