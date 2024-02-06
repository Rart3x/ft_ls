#include "../includes/ls.h"

bool add_element(s_dirs *dirs, const char *str, unsigned char type) {
    if (dirs->size == dirs->capacity) {
        dirs->arr = realloc(dirs->arr, 2 * dirs->capacity * sizeof(s_arr));
        
        if (!dirs->arr)
            return FALSE;
        
        dirs->capacity *= 2;
    }

    dirs->arr[dirs->size].str = ft_strdup(str);
    dirs->arr[dirs->size].type = type;
    dirs->size++;

    return TRUE;
}

void    define_directory_blocks(s_vars *vars) {
    struct stat file_stat;

    for (size_t i = 0; i < vars->dirs->size; i++) {
        stat(vars->dirs->arr[i].str, &file_stat);
        
        vars->dirs->arr[i].blocks = file_stat.st_blocks;
        vars->dirs->blocks += vars->dirs->arr[i].blocks;
    }
}

void    define_errors(int ac, char **av) { 
    for (size_t i = 1; i < (size_t)ac; i++) {
        DIR *dir = opendir(av[i]);

        if (!dir && av[i][0] != '-')
            err_cannot_access(av[i]);
        closedir(dir);
    }
}

void    define_file_settings(s_arr *arr) {
    define_file_date(arr);
    define_file_permissions(arr);
    define_file_size(arr); 
    define_group(arr);
    define_link(arr);
    define_owner(arr);
}

void    define_flags(s_vars *vars, int ac, char **av) {
    for (size_t i = 1; i < (size_t)ac; i++) {
        if (av[i][0] == '-') {
            for (size_t j = 0; j < ft_strlen(av[i]); j++) { 
                switch (av[i][j]) {
                    case 'a':
                        vars->flags.a = true;
                        break;
                    case 'l':
                        vars->flags.l = true;
                        break;
                    case 'r':
                        vars->flags.r = true;
                        break;
                    case 'R':
                        vars->flags.R = true;
                        break;
                    case 't':
                        vars->flags.t = true;
                        break;
                }
            }
        }
    }
}

void    define_file_date(s_arr *arr) {
    struct stat file_info;
    struct tm *local_time;

    time_t mod_time;

    stat(arr->str, &file_info);

    mod_time = file_info.st_mtime;

    local_time = localtime(&mod_time);
    if (local_time->tm_isdst > 0)
        mod_time -= 3600;

    strftime(arr->date, sizeof(arr->date), "%b %e %H:%M", local_time);
}

void    define_file_permissions(s_arr *arr) {
    struct stat file_stat;

    if (stat(arr->str, &file_stat))
        return;
    
    arr->executable = ((file_stat.st_mode & S_IXUSR) || (file_stat.st_mode & S_IXGRP) || (file_stat.st_mode & S_IXOTH));

    if (file_stat.st_mode & S_IRUSR) arr->user_permissions[0] |= TRUE;
    if (file_stat.st_mode & S_IWUSR) arr->user_permissions[1] |= TRUE;
    if (file_stat.st_mode & S_IXUSR) arr->user_permissions[2] |= TRUE;

    if (file_stat.st_mode & S_IRGRP) arr->group_permissions[0] |= TRUE;
    if (file_stat.st_mode & S_IWGRP) arr->group_permissions[1] |= TRUE;
    if (file_stat.st_mode & S_IXGRP) arr->group_permissions[2] |= TRUE;

    if (file_stat.st_mode & S_IROTH) arr->others_permissions[0] |= TRUE;
    if (file_stat.st_mode & S_IWOTH) arr->others_permissions[1] |= TRUE;
    if (file_stat.st_mode & S_IXOTH) arr->others_permissions[2] |= TRUE;

    if (lstat(arr->str, &file_stat))
        return;

    if (S_ISLNK(file_stat.st_mode))
        arr->type = 2;
}

void    define_file_size(s_arr *arr) { 
    struct stat file_info;

    stat(arr->str, &file_info);

    arr->size = (int)file_info.st_size;
}

void    define_group(s_arr *arr) {
    struct stat file_info;
    
    stat(arr->str, &file_info);

    struct group *grp = getgrgid(file_info.st_gid);
    
    if (grp != NULL)
        arr->group = strdup(grp->gr_name);
}

bool    define_is_there_directory(int ac, char **av) {
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

void    define_link(s_arr *arr) {
    struct stat file_info;

    lstat(arr->str, &file_info);

    arr->links = file_info.st_nlink;
}

void    define_nb_dir(s_vars *vars, int ac, char **av) {
    for (size_t i = 1; i < (size_t)ac; i++) {
        DIR *dir = opendir(av[i]);
    
        if (dir)
            vars->nb_dir++;
        closedir(dir);
    }
}

void    define_owner(s_arr *arr) { 
    struct stat file_info;

    stat(arr->str, &file_info);

    struct passwd *pw = getpwuid(file_info.st_uid);
    arr->owner = ft_strdup(pw->pw_name);
}