#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc <  2) {
        printf("usage: %s <directory>\n", argv[0]);
        return  1;
    }

    char buffer[BUFFER_SIZE];
    char ft_ls_cmd[BUFFER_SIZE];
    char ls_cmd[BUFFER_SIZE];

    // Construct the command for executing ft_ls
    snprintf(ft_ls_cmd, BUFFER_SIZE, "./ft_ls %s", argv[1]);

    // Append additional arguments
    for (int i =  2; i < argc; ++i) {
        size_t len = strlen(ft_ls_cmd);
        snprintf(ft_ls_cmd + len, BUFFER_SIZE - len, " %s", argv[i]);
    }

    // Execution of ft_ls
    printf("\033[34mft_ls");
    for (int i = 1; i < argc; ++i) {
        printf(" %s", argv[i]);
    }
    printf("\n\033[0m");

    FILE *ft_ls_fp = popen(ft_ls_cmd, "r");
    if (ft_ls_fp == NULL)
        return  1;

    while (fgets(buffer, BUFFER_SIZE, ft_ls_fp) != NULL) {
        printf("%s", buffer);
    }

    // Construct the command for executing ls
    snprintf(ls_cmd, BUFFER_SIZE, "ls %s", argv[1]);

    // Append additional arguments
    for (int i =  2; i < argc; ++i) {
        size_t len = strlen(ls_cmd);
        snprintf(ls_cmd + len, BUFFER_SIZE - len, " %s", argv[i]);
    }

    // Execution of ls
    printf("\033[34m\nls");
    for (int i = 1; i < argc; ++i) {
        printf(" %s", argv[i]);
    }
    printf("\n\033[0m");
    
    FILE *ls_fp = popen(ls_cmd, "r");
    if (ls_fp == NULL)
        return  1;

    while (fgets(buffer, BUFFER_SIZE, ls_fp) != NULL) {
        printf("%s", buffer);
    }

    pclose(ft_ls_fp);
    pclose(ls_fp);

    return  0;
}