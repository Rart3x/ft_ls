#include "../includes/ls.h"

void    sort_files(s_vars *vars) {
    if (vars->flags.t)
        sort_by_time(vars);
    else
        sort_by_name(vars);

    if (vars->flags.r)
        reverse_sort(vars);
}

void reverse_sort(s_vars *vars) {
    size_t start = 0;
    size_t end = vars->dirs->size - 1;

    while (start < end) {
        s_arr tmp = vars->dirs->arr[start];
        vars->dirs->arr[start] = vars->dirs->arr[end];
        vars->dirs->arr[end] = tmp;

        start++;
        end--;
    }
}

void    sort_by_name(s_vars *vars) {
    for (size_t i = 0; i < vars->dirs->size; i++) {
        for (size_t j = i + 1; j < vars->dirs->size; j++) {
            char *tmp1 = str_to_lower(vars->dirs->arr[i].str);
            char *tmp2 = str_to_lower(vars->dirs->arr[j].str);

            if (ft_strcmp(tmp1, tmp2) > 0) {
                s_arr tmp = vars->dirs->arr[i];
                vars->dirs->arr[i] = vars->dirs->arr[j];
                vars->dirs->arr[j] = tmp;
            }
            free(tmp1);
            free(tmp2);
        }
    }
}

void    sort_by_time(s_vars *vars) {
    for (size_t i = 0; i < vars->dirs->size; i++) {
        for (size_t j = i + 1; j < vars->dirs->size; j++) {
            struct stat file_stat_1;
            struct stat file_stat_2;

            stat(vars->dirs->arr[i].path, &file_stat_1);
            stat(vars->dirs->arr[j].path, &file_stat_2);

            if (file_stat_1.st_ctime < file_stat_2.st_ctime) {
                s_arr tmp = vars->dirs->arr[i];
                vars->dirs->arr[i] = vars->dirs->arr[j];
                vars->dirs->arr[j] = tmp;
            }
        }
    }
}