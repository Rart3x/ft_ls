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
        char *str;

        unsigned char type;

        bool    executable;
        bool    readable;
        bool    writable;

        bool    user_permissions[3];
        bool    group_permissions[3];
        bool    others_permissions[3];

        char    date[80];
        char    *group;
        char    *owner;

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
        s_dirs  *dirs;
        s_flags flags;

        size_t  current_dir;
        size_t  nb_dir;

    }   s_vars;

/*---------------------------Functions---------------------------*/

    /*---------------------------Init Functions---------------------------*/
        char    **init_args(char **args, int ac, char **av);
        void    init_dirs(s_dirs *dirs, const char *directory);

        void    init_struc_arr(s_arr *arr);
        void    init_struc_dirs(s_dirs *dirs);
        void    init_struc_flags(s_flags *flags);
        void    init_structs(s_vars *vars);

    /*---------------------------Without arguments functions---------------------------*/
        /*---------------------------Clear functions---------------------------*/
            void    free_dirs(s_dirs *dirs);
        /*---------------------------Print functions---------------------------*/
            void    print_ls(s_vars *vars);
            void    print_ls_long_format(s_vars *vars);
            void    print_info_long_format(s_arr *arr);
            void    print_permissions(s_arr *arr);
        /*---------------------------Sort functions---------------------------*/
        void    without_args(s_vars *vars);
    /*---------------------------With arguments functions---------------------------*/
        /*---------------------------Clear functions---------------------------*/
        /*---------------------------Print functions---------------------------*/
        /*---------------------------Sort functions---------------------------*/
        void    with_args(s_vars *vars, int ac, char **av);

    /*---------------------------Utils Functions---------------------------*/
        bool    add_element(s_dirs *dirs, const char *str, unsigned char type);

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

        bool    define_is_there_directory(int ac, char **av);