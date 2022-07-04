#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
 
int        main(void)
{
    struct stat stat_buf;
    char        *f_name;
 
    f_name = readline("> ");
    stat(f_name, &stat_buf);
    if (S_ISDIR(stat_buf.st_mode))
        printf("> %s is directory\n", f_name);
    else if (S_ISREG(stat_buf.st_mode))
        printf("> %s is regular file\n", f_name);
        // printf("file size : %lld\n", stat_buf.st_size);
    else
        perror(f_name);
    free(f_name);
    return (0);
}