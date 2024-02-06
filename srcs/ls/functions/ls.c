#include "../includes/ls.h"

void    with_args(s_vars *vars, int ac, char **av) {
    DIR *dir;

    define_errors(ac, av);
    define_flags(vars, ac, av);
    define_nb_dir(vars, ac, av);

    for (size_t i = 1; i < (size_t)ac; i++) {
        
        if (!define_is_there_directory(ac, av))
            dir = opendir(".");
        else
            dir = opendir(av[i]);

        if (dir)
        {
            if (!define_is_there_directory(ac, av))
                init_dirs(vars->dirs, ".");
            else
                init_dirs(vars->dirs, av[i]);

            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_name[0] != '.') {
                    if (!add_element(vars->dirs, entry->d_name, entry->d_type)) {
                        free_dirs(vars->dirs);
                        closedir(dir);
                        return;
                    }
                    define_file_settings(&vars->dirs->arr[vars->dirs->size - 1]);
                    define_file_date(&vars->dirs->arr[vars->dirs->size - 1]);
                    define_file_permissions(&vars->dirs->arr[vars->dirs->size - 1]);
                    define_file_size(&vars->dirs->arr[vars->dirs->size - 1]); 
                    define_group(&vars->dirs->arr[vars->dirs->size - 1]);
                    define_link(&vars->dirs->arr[vars->dirs->size - 1]);
                    define_owner(&vars->dirs->arr[vars->dirs->size - 1]);
                }
            }
            if (vars->flags.l)
                print_ls_long_format(vars);
            else
                print_ls(vars);
        }
        closedir(dir);
        free_dirs(vars->dirs);
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
                free_dirs(vars->dirs);
                closedir(dir);
                return;
            }
            define_file_permissions(&vars->dirs->arr[vars->dirs->size - 1]);
        }
    }
    print_ls(vars);
    closedir(dir);
    free_dirs(vars->dirs);
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