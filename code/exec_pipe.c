/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** exec_pipe.c
*/

#include "my.h"

static void null_comm(Hello_t *gogo)
{
    char *line = "|";

    for (int i = 0; gogo->args[i] != NULL; i++) {
        if (my_strcmp(gogo->args[0], "|") == 55 && gogo->args[1] == NULL) {
            my_printf("Invalid null command.\n");
            exit(1);
        }
    }
}

int is_pipe(Hello_t *gogo)
{
    for (int i = 0; gogo->args[i] != NULL; i++) {
        if (strcmp(gogo->args[i], "|") == 0)
            return i;
    }
    return 0;
}

static char **get_params_pipe(Hello_t *gogo)
{
    char **new_tab = malloc(sizeof(char **));
    int i = 0;

    while (strcmp(gogo->args[i], "|") != 0) {
        new_tab[i] = strdup(gogo->args[i]);
        i++;
    }
    new_tab[i] = NULL;
    return new_tab;
}

static char **create_tab_pipe(Hello_t *gogo)
{
    char **tab = malloc(sizeof(char *) * BUFSIZ);
    int i = 0;
    int y = 0;

    while (gogo->args[is_pipe(gogo) + 1 + i] != NULL) {
        tab[i] = strdup(gogo->args[is_pipe(gogo) + 1 + i]);
        i++;
    }
    tab[i] = NULL;
    return tab;
}

static int pipe_part3(Hello_t *gogo, int status, int cpid, int *fd)
{
    char **tab;
    pid_t pid;

    waitpid(cpid, &status, 0);
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    pid = fork();
    if (pid == 0 && gogo->args[0] == NULL)
        return 1;
    if (pid == 0 && strlen(gogo->args[0]) > 0) {
        tab = create_tab_pipe(gogo);
        execvp(tab[0], tab);
    } else {
        wait(&status);
        return (status);
    }
}

static int pipe_part2(Hello_t *gogo, int status, int cpid, int *fd)
{
    if (cpid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execvp(gogo->args[0], get_params_pipe(gogo));
        return 1;
    } else {
        return pipe_part3(gogo, status, cpid, fd);
    }
}

static int multi_pipe_handling(Hello_t *gogo)
{
    int cpt = 0;

    for (int i = 0; gogo->args[i] != NULL; i++) {
        if (strcmp(gogo->args[i], "|") == 0)
            cpt++;
    }
    if (cpt > 1)
        return -1;
    return 0;
}

int exec_pipe(Hello_t *gogo, char **env)
{
    int status = 2;
    int fd[2];
    char **tab;
    int cpid;

    null_comm(gogo);
    gogo->bzez = 77;
    if (multi_pipe_handling(gogo) == -1)
        return 0;
    pipe(fd);
    cpid = fork();
    return pipe_part2(gogo, status, cpid, fd);
}
