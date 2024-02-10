#pragma once

/*---------------------------Macros---------------------------*/
    #define EACCES // Access forbidden.

    #define EBADF // fd is not a valid open file descriptor for reading.

    #define EMFILE // Too many file descriptors are open for the calling process.

    #define ENFILE // Too many files are open on the system.

    #define ENOENT_FMT "ls: cannot access '%s': No such file or directory\n"
    #define ENOENT(file) printf(ENOENT_FMT, (file)) // Directory does not exist, or name is an empty string.

    #define ENOMEM // Not enough memory to complete the operation.

    #define ENOTDIR // name is not a directory.

    #define INVALID_OPTION_FMT "ls: invalid option -- '%c'\nEnter « ls --help » for more information.\n" // Invalid option.
    #define INVALID_OPTION(file) printf(INVALID_OPTION_FMT, (file)) // Invalid option.

/*---------------------------Functions---------------------------*/
    void    err_cannot_access(char *err_message);
    void    err_invalid_option(char *err_message);