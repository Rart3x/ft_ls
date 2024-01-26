#include "../includes/ls.h"

void    free_dirs(s_dirs *dirs) {
    if (dirs != NULL) {
        free(dirs->directory);
        free(dirs->arr);
        free(dirs);
    }
}