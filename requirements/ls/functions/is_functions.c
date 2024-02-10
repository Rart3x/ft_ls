#include "../includes/ls.h"

bool    is_directory(const char *str) {
    struct stat file_stat;

    if (stat(str, &file_stat) != 0)
        return FALSE;
    if (S_ISDIR(file_stat.st_mode))
        return TRUE;
    return FALSE;
}

bool    is_flag(const char *str) {
    if (!str)
        return FALSE;

    if (str[0] == '-' && (str[1] == 'a' || str[1] == 'l' || str[1] == 'R' || str[1] == 'r' || str[1] == 't' || str[1] == '1'))
        return TRUE;
    return FALSE;
}

bool    is_file_exist(const char *str) {
    struct stat file_stat;

    if (stat(str, &file_stat) != 0)
        return FALSE;
    return TRUE;
}

bool    is_there_directory(int ac, char **av) {
    for (size_t i = 1; i < (size_t)ac; i++) {
        DIR *dir = opendir(av[i]);

        if (dir) {
            closedir(dir);
            return true;
        }
        closedir(dir);
    }
    return false;
}