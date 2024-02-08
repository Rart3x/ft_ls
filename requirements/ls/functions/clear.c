#include "../includes/ls.h"

void free_dirs(s_dirs *dirs) {
    s_dirs *current = dirs;

    while (current) {
        s_dirs *next = current->next;

        if (current->arr && current->directory) {
            while (current->size >  0) {
                if (current->arr[current->size -  1].group)
                    free(current->arr[current->size -  1].group);
                if (current->arr[current->size -  1].owner)
                    free(current->arr[current->size -  1].owner);
                if (current->arr[current->size -  1].str)
                    free(current->arr[current->size -  1].str);
                if (current->arr[current->size -  1].path)
                    free(current->arr[current->size -  1].path);
                current->size--;
            }
            free(current->arr);
            free(current->directory);
        }
        free(current);
        current = next;
    }
}
