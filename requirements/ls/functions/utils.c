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

void    define_directory_blocks(s_vars *vars) {
    struct stat file_stat;

    for (size_t i = 0; i < vars->dirs->size; i++) {
        stat(vars->dirs->arr[i].path, &file_stat);

        // Size of the file system block (in bytes)
        long bloc_size = file_stat.st_blksize;

        // Size of the file in bytes
        long file_size_bytes = file_stat.st_size;

        // Size of the file in blocks
        long file_size_blocks = (file_size_bytes + bloc_size - 1) / bloc_size;

        vars->dirs->arr[i].blocks = file_size_blocks * 4;
        vars->dirs->blocks += file_size_blocks * 4;
    }
}

void    define_errors(int ac, char **av) { 
    for (size_t i = 1; i < (size_t)ac; i++) {
        DIR *dir = opendir(av[i]);

        if (!dir && av[i][0] != '-' && !is_file_exist(av[i]))
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

size_t    define_flags(s_vars *vars, int ac, char **av) {
    for (size_t i = 1; i < (size_t)ac; i++) {
        if (av[i][0] == '-') {
            for (size_t j = 0; j < ft_strlen(av[i]); j++) { 
                if (!is_flag(av[i]))
                    return j + 1;

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
    return -1;
}

void    define_file_date(s_arr *arr) {
    struct stat file_info;
    struct tm *local_time;

    time_t mod_time;

    stat(arr->path, &file_info);

    mod_time = file_info.st_mtime;

    local_time = localtime(&mod_time);
    if (local_time->tm_isdst > 0)
        mod_time -= 3600;

    strftime(arr->date, sizeof(arr->date), "%b %e %H:%M", local_time);
}

void define_file_permissions(s_arr *arr) {
    struct stat file_stat;

    if (stat(arr->path, &file_stat))
        return;

    for (size_t i = 0; i < 3; i++) {
        arr->user_permissions[i] = false;
        arr->group_permissions[i] = false;
        arr->others_permissions[i] = false;
    }
    
    // Check if the file is executable by the user, group, or others
    // If it is, set arr->executable to TRUE
    arr->executable = ((file_stat.st_mode & S_IXUSR) || (file_stat.st_mode & S_IXGRP) || (file_stat.st_mode & S_IXOTH));

    // Check the user permissions for the file
    // If the user has read, write, or execute permissions, set the corresponding index in arr->user_permissions to TRUE
    if (file_stat.st_mode & S_IRUSR) arr->user_permissions[0] |= TRUE;
    if (file_stat.st_mode & S_IWUSR) arr->user_permissions[1] |= TRUE;
    if (file_stat.st_mode & S_IXUSR) arr->user_permissions[2] |= TRUE;

    // Check the group permissions for the file
    // If the group has read, write, or execute permissions, set the corresponding index in arr->group_permissions to TRUE
    if (file_stat.st_mode & S_IRGRP) arr->group_permissions[0] |= TRUE;
    if (file_stat.st_mode & S_IWGRP) arr->group_permissions[1] |= TRUE;
    if (file_stat.st_mode & S_IXGRP) arr->group_permissions[2] |= TRUE;

    // Check the permissions for others for the file
    // If others have read, write, or execute permissions, set the corresponding index in arr->others_permissions to TRUE
    if (file_stat.st_mode & S_IROTH) arr->others_permissions[0] |= TRUE;
    if (file_stat.st_mode & S_IWOTH) arr->others_permissions[1] |= TRUE;
    if (file_stat.st_mode & S_IXOTH) arr->others_permissions[2] |= TRUE;

    // The lstat function is similar to stat, but if the file is a symbolic link, it fetches the attributes of the link itself, not the file it points to
    // If lstat returns a non-zero value, it means an error occurred, so we return from the function
    if (lstat(arr->path, &file_stat))
        return;

    // Check if the file is a symbolic link
    if (S_ISLNK(file_stat.st_mode))
        arr->type = 2;
}

void    define_file_size(s_arr *arr) { 
    struct stat file_info;

    stat(arr->path, &file_info);

    arr->size = (int)file_info.st_size;
}

void    define_group(s_arr *arr) {
    struct stat file_info;
    
    stat(arr->path, &file_info);

    struct group *grp = getgrgid(file_info.st_gid);
    
    arr->group = strdup(grp->gr_name);
}

void    define_link(s_arr *arr) {
    struct stat file_info;

    lstat(arr->path, &file_info);

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

    stat(arr->path, &file_info);

    struct passwd *pw = getpwuid(file_info.st_uid);
    arr->owner = ft_strdup(pw->pw_name);
}

void    define_subdirs(s_vars *vars, char *actual_dir) {
    DIR             *dir;
    DIR             *subdir;
    struct dirent   *entry;

    if ((dir = opendir(actual_dir))) {
        while ((entry = readdir(dir))) {
            char *full_path;
         
            if (entry->d_name[0] != '.') {
                full_path = ft_strjoin(actual_dir, entry->d_name);
                if ((subdir = opendir(full_path)) && full_path[0] != '.') {
                    recursive(vars, full_path);
                    define_subdirs(vars, full_path);
                    closedir(subdir);
                }
                free(full_path);
            }
        }
    }
    closedir(dir);
    (void)vars;
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