#include "../../includes/ls.h"

void    print_ls_wa(s_vars *vars) {
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