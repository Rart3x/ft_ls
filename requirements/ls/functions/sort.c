#include "../includes/ls.h"

void    sort_files(s_vars *vars) {
    if (vars->flags.t)
        sort_by_time(vars);
    else
        sort_by_name(vars);
}

void    sort_by_name(s_vars *vars) {
    for (size_t i = 0; i < vars->dirs->size; i++) {
        for (size_t j = i + 1; j < vars->dirs->size; j++) {
            if (ft_strcmp(vars->dirs->arr[i].str, vars->dirs->arr[j].str) > 0) {
                s_arr tmp = vars->dirs->arr[i];
                vars->dirs->arr[i] = vars->dirs->arr[j];
                vars->dirs->arr[j] = tmp;
            }
        }
    }
}

void    sort_by_time(s_vars *vars) {
    for (size_t i = 0; i < vars->dirs->size; i++) {
        for (size_t j = i + 1; j < vars->dirs->size; j++) {
            struct stat file_stat_1;
            struct stat file_stat_2;

            stat(vars->dirs->arr[i].str, &file_stat_1);
            stat(vars->dirs->arr[j].str, &file_stat_2);

            if (file_stat_1.st_mtime < file_stat_2.st_mtime) {
                s_arr tmp = vars->dirs->arr[i];
                vars->dirs->arr[i] = vars->dirs->arr[j];
                vars->dirs->arr[j] = tmp;
            }
        }
    }
}