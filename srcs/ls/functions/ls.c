#include "../includes/ls.h"

void    without_args(s_vars *vars) {
    (void)vars;
    DIR *dir = opendir(".");
    struct dirent *entry = readdir(dir);

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}    


int main(int ac, char **av) {
    s_vars vars;

    init_structs(&vars);
    vars.args.arr = init_args(vars.args.arr, ac, av);

    if (ac == 1)
        without_args(&vars);

    return (0);
}