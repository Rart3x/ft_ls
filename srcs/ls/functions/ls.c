#include "../includes/ls.h"

bool add_element(s_dirs *dirs, const char *str, unsigned char type) {
    if (dirs->size == dirs->capacity) {
        s_arr *new_arr = realloc(dirs->arr, 2 * dirs->capacity * sizeof(s_arr));

        if (new_arr == NULL)
            return FALSE;

        dirs->arr = new_arr;
        dirs->capacity *= 2;
    }

    dirs->arr[dirs->size].str = strdup(str);
    dirs->arr[dirs->size].type = type;
    dirs->size++;

    return TRUE;
}

void    print_ls(s_vars *vars) {
    for (size_t i = 0; i < vars->dirs.size; i++) {
        switch (vars->dirs.arr[i].type) {
            case 4:
                ft_printf(BLUE "%s" RESET, vars->dirs.arr[i].str);
                break;
            case 8:
                ft_printf(GREEN "%s" RESET, vars->dirs.arr[i].str);
                break;
            default:
                ft_printf("%s\n", vars->dirs.arr[i].str);
                break;
        }
        ft_printf(" ");
    }
    ft_printf("\n");
}

void    without_args(s_vars *vars) {
    DIR *dir = opendir(".");
    if (dir == NULL)
        return;

    vars->dirs = *init_dirs(".");

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            if (!add_element(&vars->dirs, entry->d_name, entry->d_type)) {
                free_dirs(&vars->dirs);
                closedir(dir);
                return;
            }
        }
    }
    closedir(dir);
}

int main(int ac, char **av) {
    s_vars vars;

    (void)av;

    init_structs(&vars);

    if (ac == 1)
        without_args(&vars);

    print_ls(&vars);
    // free_dirs(&vars.dirs);

    return 0;
}