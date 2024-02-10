#include "../includes/ls.h"

void    recursive(s_vars *vars, char *directory) {
    bool tmp = false;
    DIR *dir = opendir(directory);

    if (dir && is_file_exist(directory))
    {
        init_dirs(vars->dirs, directory);

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            tmp = false;
            if (is_file_exist(directory) && !is_directory(directory)) {
                if (!add_element(vars->dirs, directory, entry->d_type)) {
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
            char *path;
            char *full_path; 

            if (vars->dirs->directory[0] != '.') {
                path = ft_strjoin(vars->dirs->directory, "/");
                full_path = ft_strjoin(path, entry->d_name);

                if (is_directory(full_path) && entry->d_name[0] != '.')
                    define_subdirs(vars, full_path);
                free(path);
                free(full_path);
            }
        }
        if (!tmp) {
            if (!vars->flags.l)
                print_ls(vars, FALSE);
            else
                print_ls_long_format(vars);
        }
    }
}

void    with_args(s_vars *vars, int ac, char **av) {
    bool    tmp = false;
    DIR     *dir;
    int     invalid_option;

    define_errors(ac, av);
    if ((invalid_option = define_flags(vars, ac, av)) != -1) {
        err_invalid_option(av[invalid_option]);
        return;
    }
    define_nb_dir(vars, ac, av);

    for (size_t i = 1; i < (size_t)ac; i++) {
        
        char *directory;

        if (!is_there_directory(ac, av)) {
            dir = opendir(".");
            directory = ft_strdup(".");
        }
        else {
            dir = opendir(av[i]);
            directory = ft_strdup(av[i]);
        }

        while (is_flag(directory) && i < (size_t)ac)
            i++;

        if (dir && is_file_exist(directory))
        {
            if (!is_there_directory(ac, av))
                init_dirs(vars->dirs, ".");
            else
                init_dirs(vars->dirs, directory);

            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                tmp = false;
                if (is_file_exist(directory) && !is_directory(directory)) {
                    if (!add_element(vars->dirs, directory, entry->d_type)) {
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
            char *path;

            if (!tmp) {
                if (!vars->flags.l)
                    print_ls(vars, FALSE);
                else
                    print_ls_long_format(vars);
            }

            if (directory[0] != '.') {
                path = ft_strjoin(directory, "/");

                if (is_directory(path) && path[0] != '.' && vars->flags.R)
                    define_subdirs(vars, path);
                free(path);
            }
        }
        closedir(dir);
        free_dirs(vars->dirs);
        free(directory);
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

    free(vars.dirs);
    return (0);
}