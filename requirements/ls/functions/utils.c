#include "../includes/ls.h"

bool add_element(s_dirs *dirs, const char *str, unsigned char type) {
    if (dirs->size == dirs->capacity) {
        dirs->arr = realloc(dirs->arr, 2 * dirs->capacity * sizeof(s_arr));
        
        if (!dirs->arr)
            return FALSE;
        
        dirs->capacity *= 2;
    }
    char *path = NULL;

    if (dirs->directory[ft_strlen(dirs->directory) - 1] != '/') {
        path = ft_strjoin(dirs->directory, "/");
        dirs->arr[dirs->size].path = ft_strjoin(path, str);
    }
    else
        dirs->arr[dirs->size].path = ft_strjoin(dirs->directory, str);

    dirs->arr[dirs->size].str = ft_strdup(str);
    dirs->arr[dirs->size].type = type;

    dirs->size++;

    free(path);

    return TRUE;
}

char    *str_to_lower(const char *str) {
    size_t len = ft_strlen(str);
    char *new_str = (char *)malloc(len + 1);

    if (!new_str)
        return NULL;

    ft_strcpy(new_str, str);

    for (size_t i = 0; i < len; i++) {
        if (new_str[i] >= 'A' && new_str[i] <= 'Z') {
            new_str[i] += 32;
        }
    }
    return new_str;
}