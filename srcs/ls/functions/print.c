#include "../includes/ls.h"

void    print_ls(s_vars *vars) {
    // sort_files(vars);

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

    ft_printf("Total %d\n", vars->dirs->blocks);
    ft_printf("%s:\n", vars->dirs->directory);
    // for (size_t i = 0; i < vars->dirs->size; i++) {

    //     switch (vars->dirs->arr[i].type) {
    //         case 4:
    //             ft_printf(BLUE "%d %s" RESET, vars->dirs->arr[i].blocks ,vars->dirs->arr[i].str);
    //             break;
    //         case 8:
    //             switch (vars->dirs->arr[i].executable) {
    //                 case true:
    //                     ft_printf(GREEN "%d %s" RESET, vars->dirs->arr[i].blocks, vars->dirs->arr[i].str);
    //                     break;
    //                 case false:
    //                     ft_printf("%d %s", vars->dirs->arr[i].blocks, vars->dirs->arr[i].str);
    //                     break;
    //             }
    //             break;
    //         default:
    //             ft_printf("%s\n", vars->dirs->arr[i].str);
    //             break;
    //     }
    //     ft_printf("  ");
    // }
    if (vars->current_dir)
        ft_printf("\n\n");
    else
        ft_printf("\n");
 
    vars->current_dir++;
}