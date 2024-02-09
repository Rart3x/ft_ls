#pragma once

/*---------------------------Libft includes---------------------------*/
    #include "../../libft/include/libft.h"

/*---------------------------.h includes---------------------------*/
    #include "enum.h"
    #include "errors.h"

/*---------------------------Libs includes---------------------------*/
    #include <dirent.h>
    #include <grp.h>
    #include <pwd.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/xattr.h>
    #include <time.h>
    #include <unistd.h>

/*---------------------------Structs---------------------------*/
    typedef struct t_arr { 

        unsigned char type;

        bool    executable;
        bool    readable;
        bool    writable;

        bool    group_permissions[3];
        bool    others_permissions[3];
        bool    user_permissions[3];

        char    date[80];
        char    *group;
        char    *owner;
        char    *str;
        char    *path;

        size_t  blocks;

        int     links;
        int     size;

    }   s_arr;

    typedef struct t_dirs {
        s_arr   *arr;
        char    *directory;

        size_t  blocks;
        size_t  capacity;
        size_t  size; 

        struct t_dirs *next;

    }   s_dirs;

    typedef struct t_flags {
        bool a;
        bool l;
        bool r;
        bool R;
        bool t;

    }   s_flags;

    typedef struct t_vars {
        s_dirs      *dirs;
        s_flags     flags;

        size_t  current_dir;
        size_t  nb_dir;

    }   s_vars;

/*---------------------------Functions---------------------------*/

    /*---------------------------Init Functions---------------------------*/
        void    init_dirs(s_dirs *dirs, const char *directory);

        void    init_struc_arr(s_arr *arr);
        void    init_struc_dirs(s_dirs *dirs);
        void    init_struc_flags(s_flags *flags);
        void    init_structs(s_vars *vars);
    /*---------------------------Clear functions---------------------------*/
        void    free_dirs(s_dirs *dirs);
    /*---------------------------Sort functions---------------------------*/
        void    sort_by_name(s_vars *vars);
        void    sort_by_time(s_vars *vars);
        void    sort_files(s_vars *vars);
    /*---------------------------Print functions---------------------------*/
        void    print_ls(s_vars *vars, bool print_dir_name);
        void    print_ls_long_format(s_vars *vars);
        void    print_info_long_format(s_arr *arr);
        void    print_permissions(s_arr *arr);
    /*---------------------------Utils Functions---------------------------*/
        bool    add_element(s_dirs *dirs, const char *str, unsigned char type);
        /*---------------------------Define Functions---------------------------*/
            void    define_directory_blocks(s_vars *vars);
            void    define_errors(int ac, char **av);
            void    define_flags(s_vars *vars, int ac, char **av);
            void    define_file_date(s_arr *arr);
            void    define_file_permissions(s_arr *arr);
            void    define_file_settings(s_arr *arr);
            void    define_file_size(s_arr *arr);
            void    define_group(s_arr *arr);
            void    define_link(s_arr *arr);
            void    define_nb_dir(s_vars *vars, int ac, char **av);
            void    define_owner(s_arr *arr);
            void    define_subdirs(s_vars *vars, char *actual_dir);
        /*---------------------------Is Functions---------------------------*/
            bool    is_directory(const char *str);
            bool    is_file_exist(const char *str);
            bool    is_flag(const char *str);
            bool    is_there_directory(int ac, char **av);

        /*---------------------------Main Functions---------------------------*/
            void    recursive(s_vars *vars, char *directory);
            void    with_args(s_vars *vars, int ac, char **av);
            void    without_args(s_vars *vars);