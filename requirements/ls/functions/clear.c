#include "../includes/ls.h"

void free_dirs(s_dirs *dirs) {
    while (dirs) {
        s_dirs *next = dirs->next;

        if (dirs->arr) {
            for (size_t i = 0; i < dirs->size; i++) {
                if (dirs->arr[i].group) {
                    free(dirs->arr[i].group);
                    dirs->arr[i].group = NULL;
                }
                if (dirs->arr[i].owner) {
                    free(dirs->arr[i].owner);
                    dirs->arr[i].owner = NULL;
                }
                if (dirs->arr[i].str) {
                    free(dirs->arr[i].str);
                    dirs->arr[i].str = NULL;
                }
                if (dirs->arr[i].path) {
                    free(dirs->arr[i].path);
                    dirs->arr[i].path = NULL;
                }
            }
            free(dirs->arr);
            dirs->arr = NULL;
        }

        if (dirs->directory) {
            free(dirs->directory);
            dirs->directory = NULL;
        }
        dirs = next;
    }
}