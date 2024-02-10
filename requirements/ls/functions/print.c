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

void    print_ls(s_vars *vars, bool print_dir_name) {
    sort_files(vars);

    if (print_dir_name) {
        switch (vars->dirs->arr[0].type) {
            case 4:
                ft_printf(BLUE "%s" RESET, vars->dirs->arr[0].str);
                break;
            case 8:
                switch (vars->dirs->arr[0].executable) {
                    case true:
                        ft_printf(GREEN "%s" RESET, vars->dirs->arr[0].str);
                        break;
                    case false:
                        ft_printf("%s", vars->dirs->arr[0].str);
                        break;
                }
                break;
            default:
                ft_printf("%s\n", vars->dirs->arr[0].str);
                break;
        }
    }
    else {
        printf("Total %ld\n", vars->dirs->blocks);

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
    }

    if (vars->current_dir)
        ft_printf("\n\n");
    else
        ft_printf("\n");
 
    vars->current_dir++;
}

void    print_ls_long_format(s_vars *vars, bool print_dir_name) {
    sort_files(vars);

    define_directory_blocks(vars);

    if (print_dir_name) { 
        switch (vars->dirs->arr[0].type) {
            case 4:
                print_info_long_format(&vars->dirs->arr[0]);
                ft_printf(BLUE "%s\n" RESET, vars->dirs->arr[0].str);
                break;
            case 8:
                switch (vars->dirs->arr[0].executable) {
                    case true:
                        print_info_long_format(&vars->dirs->arr[0]);
                        ft_printf(GREEN "%s\n" RESET, vars->dirs->arr[0].str);
                        break;
                    case false:
                        print_info_long_format(&vars->dirs->arr[0]);
                        ft_printf("%s\n", vars->dirs->arr[0].str);
                        break;
                }
                break;
            default:
                print_info_long_format(&vars->dirs->arr[0]);
                ft_printf("%s\n", vars->dirs->arr[0].str);
                break;
        }
    }
    else {
        ft_printf("Total %d\n", vars->dirs->blocks);

        if (vars->nb_dir > 1)
                ft_printf("%s:\n", vars->dirs->directory);

            for (size_t i = 0; i < vars->dirs->size; i++) {
                switch (vars->dirs->arr[i].type) {
                    case 4:
                        print_info_long_format(&vars->dirs->arr[i]);
                        ft_printf(BLUE "%s\n" RESET, vars->dirs->arr[i].str);
                        break;
                    case 8:
                        switch (vars->dirs->arr[i].executable) {
                            case true:
                                print_info_long_format(&vars->dirs->arr[i]);
                                ft_printf(GREEN "%s\n" RESET, vars->dirs->arr[i].str);
                                break;
                            case false:
                                print_info_long_format(&vars->dirs->arr[i]);
                                ft_printf("%s\n", vars->dirs->arr[i].str);
                                break;
                        }
                        break;
                    default:
                        print_info_long_format(&vars->dirs->arr[i]);
                        ft_printf("%s\n", vars->dirs->arr[i].str);
                        break;
                }
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

void    print_info_long_format(s_arr *arr) { 
    print_file_type(arr->type);
    print_permissions(arr);
    ft_printf("%d ", arr->links);
    ft_printf("%s %s ", arr->owner, arr->group);
    ft_printf("%d ", arr->size);
    ft_printf("%s ", arr->date);
}