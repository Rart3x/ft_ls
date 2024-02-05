#include "../includes/ls.h"

void    print_file_type(unsigned char type) {
    switch (type) { 
        case 2:
            ft_printf("l");
            break;
        case 4:
            ft_printf("d");
            break;
        default:
            ft_printf("-");
            break;
    }
}

void    print_ls(s_vars *vars) {
    // sort_files(vars);

    if (vars->nb_dir > 1)
        ft_printf("%s:\n", vars->dirs->directory);
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
    if (vars->current_dir)
        ft_printf("\n\n");
    else
        ft_printf("\n");
 
    vars->current_dir++;
}

void    print_ls_long_format(s_vars *vars) {

    // sort_files(vars);

    define_directory_blocks(vars);

    for (size_t i = 0; i < vars->dirs->size; i++) {
        switch (vars->dirs->arr[i].type) {
            case 4:
                print_file_type(vars->dirs->arr[i].type);
                print_permissions(&vars->dirs->arr[i]);
                ft_printf("%d ", vars->dirs->arr[i].links);
                ft_printf("%s %s ", vars->dirs->arr[i].owner, vars->dirs->arr[i].group);
                ft_printf("%d ", vars->dirs->arr[i].size);
                ft_printf("%s ", vars->dirs->arr[i].date);
                ft_printf(BLUE "%s\n" RESET, vars->dirs->arr[i].str);
                break;
            case 8:
                switch (vars->dirs->arr[i].executable) {
                    case true:
                        print_file_type(vars->dirs->arr[i].type);
                        print_permissions(&vars->dirs->arr[i]);
                        ft_printf("%d ", vars->dirs->arr[i].links);
                        ft_printf("%s %s ", vars->dirs->arr[i].owner, vars->dirs->arr[i].group);
                        ft_printf("%d ", vars->dirs->arr[i].size);
                        ft_printf("%s ", vars->dirs->arr[i].date);
                        ft_printf(GREEN "%s\n" RESET, vars->dirs->arr[i].str);
                        break;
                    case false:
                        print_file_type(vars->dirs->arr[i].type);
                        print_permissions(&vars->dirs->arr[i]);
                        ft_printf("%d ", vars->dirs->arr[i].links);
                        ft_printf("%s %s ", vars->dirs->arr[i].owner, vars->dirs->arr[i].group);
                        ft_printf("%d ", vars->dirs->arr[i].size);
                        ft_printf("%s ", vars->dirs->arr[i].date);
                        ft_printf("%s\n", vars->dirs->arr[i].str);
                        break;
                }
                break;
            default:
                print_file_type(vars->dirs->arr[i].type);
                print_permissions(&vars->dirs->arr[i]);
                ft_printf("%d ", vars->dirs->arr[i].links);
                ft_printf("%s %s ", vars->dirs->arr[i].owner, vars->dirs->arr[i].group);
                ft_printf("%d ", vars->dirs->arr[i].size);
                ft_printf("%s ", vars->dirs->arr[i].date);
                ft_printf("%s\n", vars->dirs->arr[i].str);
                break;
        }
    }
    vars->current_dir++;
}

void    print_permissions(s_arr *arr) {
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            switch (i) {
                case 0:
                    switch (arr->user_permissions[j]) {
                        case TRUE:
                            switch (j) {
                                case 0:
                                    ft_printf("r");
                                    break;
                                case 1:
                                    ft_printf("w");
                                    break;
                                case 2:
                                    ft_printf("x");
                                    break;
                            }
                            break;
                        case FALSE:
                            ft_printf("-");
                            break;
                    }
                    break;
                case 1:
                    switch (arr->group_permissions[j]) {
                        case TRUE:
                            switch (j) {
                                case 0:
                                    ft_printf("r");
                                    break;
                                case 1:
                                    ft_printf("w");
                                    break;
                                case 2:
                                    ft_printf("x");
                                    break;
                            }
                            break;
                        case FALSE:
                            ft_printf("-");
                            break;
                    }
                    break;
                case 2:
                    switch (arr->others_permissions[j]) {
                        case TRUE:
                            switch (j) {
                                case 0:
                                    ft_printf("r");
                                    break;
                                case 1:
                                    ft_printf("w");
                                    break;
                                case 2:
                                    ft_printf("x");
                                    break;
                            }
                            break;
                        case FALSE:
                            ft_printf("-");
                            break;
                    }
                    break;
            }
        }
    }
    ft_printf(" ");
}