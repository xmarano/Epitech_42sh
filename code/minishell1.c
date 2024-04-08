/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** main.c
*/

#include "my.h"

static int stati(void)
{
    int status;
    int is = 0;

    wait(&status);
    if ((WEXITSTATUS(status) == 55) && isatty(0) != 1)
        exit(1);
    if (WIFEXITED(status)) {
        return (WEXITSTATUS(status));
    } else if (WIFEXITED(status) == is) {
        my_printf("Segmentation fault\n");
        return 0;
    }
}

static int suite(Hello_t *gogo, char **env)
{
    if (gogo->args[0][0] == '/' || gogo->args[0][0] == '.') {
        execve(gogo->args[0], gogo->args, env);
        look_errno(gogo);
        exit(0);
    } else
        cat_the_bin(gogo, env);
    return 0;
}

static int look_dir(Hello_t *gogo)
{
    struct stat st;

    if (stat(gogo->args[0], &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            my_printf("%s: Permission denied.\n", gogo->args[0]);
            return ex_or_rt();
        }
    }
}

static int prompt(void)
{
    char current_dir[BUFFER_SIZE];

    my_printf("-> Minishell--");
    getcwd(current_dir, sizeof(current_dir));
    my_printf("\033[34;01m%s\033[00m -> ", current_dir);
}

static void duym(void)
{
    if (isatty(0) == 1)
        prompt();
}

static int test(Hello_t *gogo)
{
    if (!isatty(0) == 1) {
        if (gogo->args[0] == NULL)
            return 1;
    }
    return 0;
}

static int tokenisation(Hello_t *gogo)
{
    while (gogo->token != NULL) {
        gogo->args[gogo->i] = gogo->token;
        gogo->token = strtok(NULL, " \t\n");
        gogo->i++;
    }
}

static int what_fct(Hello_t *gogo, int i, char *file, char **env)
{
    if (i == 1 && gogo->n == 4)
        redir_left(gogo, file, env);
    else if (i == 1)
        redir_right(gogo, file, env);
    else
        suite(gogo, env);
}

int execute_fork(int ac, char **av, char **env, Hello_t *gogo)
{
    char *type = gogo->args[0];
    char *file = NULL;
    int i = 0;

    if (my_strcmp2(type, "env") == 55 ||
        my_strcmp2(type, "setenv") == 55 || my_strcmp2(type, "unsetenv") == 55)
        return all_env(ac, av, env, gogo);
    if (my_strcmp2(type, "cd") == 55)
        return build_cd(gogo, env);
    file = look_redirect(gogo);
    if (file != NULL)
        i = 1;
    gogo->pid = fork();
    if (gogo->pid == 0) {
        what_fct(gogo, i, file, env);
    } else
        return (stati());
}

int mini_shell(int ac, char **av, char **env, Hello_t *gogo)
{
    while (parsing_input(gogo) == 0) {
        tokenisation(gogo);
        gogo->args[gogo->i] = NULL;
        if (test(gogo) == 1)
            return 0;
        if (gogo->args[0] == NULL || gogo->args[0][0] == '\t') {
            duym();
            continue;
        }
        if (my_strcmp2(gogo->args[0], "exit") == 55)
            exit(0);
        if (look_dir(gogo) == 1)
            return 1;
        if (!isatty(0) == 1) {
            execute_fork(ac, av, env, gogo);
            return mini_shell(ac, av, env, gogo);
        }
        execute_fork(ac, av, env, gogo);
        duym();
    }
}
