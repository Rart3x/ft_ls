#include "../../includes/ls.h"

void    free_dirs_wa(s_dirs *dirs) {
    if (dirs != NULL) {
        if (dirs->arr != NULL) {
            while (dirs->size > 0) {
                free(dirs->arr[dirs->size - 1].str);
                dirs->size--;
            }
        }
        free(dirs->directory);
        free(dirs->arr);
        free(dirs);
    }
}