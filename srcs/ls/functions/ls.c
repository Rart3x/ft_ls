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

void    define_file_permissions(s_arr *arr) {
    struct stat file_stat;

    stat(arr->str, &file_stat);

    arr->executable = (file_stat.st_mode & S_IXUSR) ? true : false;
    arr->readable = (file_stat.st_mode & S_IRUSR) ? true : false;
    arr->writable = (file_stat.st_mode & S_IWUSR) ? true : false;
}

void    print_ls(s_vars *vars) {
    // sort_files(vars);

    for (size_t i = 0; i < vars->dirs->size; i++) {
        switch (vars->dirs->arr[i].type) {
            case 4:
                ft_printf(BLUE "%s" RESET, vars->dirs->arr[i].str);
                break;
            case 8:
                switch (vars->dirs->arr[i].executable) {
                    case true:
                        ft_printf(GREEN "%s" RESET, vars->dirs->arr[i].str);
                        break;
                    case false:
                        ft_printf("%s", vars->dirs->arr[i].str);
                        break;
                }
                break;
            default:
                ft_printf("%s\n", vars->dirs->arr[i].str);
                break;
        }
        ft_printf("  ");
    }
    ft_printf("\n");
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
                // free_dirs(&vars->dirs);
                closedir(dir);
                return;
            }
            define_file_permissions(&vars->dirs->arr[vars->dirs->size - 1]);
        }
    }
    closedir(dir);
    print_ls(vars);
    free_dirs(vars->dirs);
}

int main(int ac, char **av) {
    s_vars vars;

    (void)av;

    init_structs(&vars);

    if (ac == 1)
        without_args(&vars);


    return (0);
}