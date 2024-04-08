/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-yanis.prevost
** File description:
** redir.c
*/

#include "my.h"

static int is_dir(char *file)
{
    struct stat st;

    if (stat(file, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            my_printf("%s: Is a directory.\n", file);
            return 1;
        }
    }
}

char *bogoss(char *file, Hello_t *gogo, int i)
{
    file = gogo->args[i + 1];
    gogo->args[i] = NULL;
    return file;
}

char *look_redirect(Hello_t *gogo)
{
    char *file = NULL;

    for (int i = 0; gogo->args[i] != NULL; i++) {
        if (my_strcmp2(gogo->args[i], ">") == 55) {
            file = bogoss(file, gogo, i);
            break;
        }
        if (my_strcmp2(gogo->args[i], "<") == 55) {
            file = bogoss(file, gogo, i);
            gogo->n = 4;
            break;
        }
        if (my_strcmp2(gogo->args[i], ">>") == 55) {
            file = bogoss(file, gogo, i);
            gogo->n = 3;
            break;
        }
    }
    return file;
}

int redir_right(Hello_t *gogo, char *file, char **env)
{
    int fd;
    char *command = gogo->args[0];

    if (gogo->n == 3)
        fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    else
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (is_dir(file) == 1 || fd == -1)
        exit(1);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    if (command[0] == '/' || command[0] == '.') {
        execve(command, gogo->args, env);
        exit(1);
    } else {
        cat_the_bin(gogo, env);
    }
}

int redir_left(Hello_t *gogo, char *file, char **env)
{
    int fd;
    char *command = gogo->args[0];

    fd = open(file, O_RDONLY);
    if (fd == -1 || is_dir(file) == 1) {
        exit(1);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    if (command[0] == '/' || command[0] == '.') {
        execve(command, gogo->args, env);
        exit(1);
    } else {
        cat_the_bin(gogo, env);
    }
}
