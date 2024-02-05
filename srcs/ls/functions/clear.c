#include "../includes/ls.h"

void free_dirs(s_dirs *dirs) {
    s_dirs *current = dirs;

    while (current) {
        s_dirs *next = current->next;

        if (current->arr) {
            while (current->size > 0) {
                free(current->arr[current->size - 1].str);
                free(current->arr[current->size - 1].owner);
                current->size--;
            }
            free(current->arr);
            free(current->directory);
        }
        free(current);
        current = next;
    }
}