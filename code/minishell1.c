/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-42sh-anthony.colombani-gailleur
** File description:
** minishell1.c
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

char *concatenate_strings(char **strings)
{
    size_t total_length = 0;
    char *result;
    size_t offset = 0;

    for (int i = 0; strings[i] != NULL; i++) {
        total_length += strlen(strings[i]);
    }
    result = (char *)malloc(total_length + 1);
    for (int i = 0; strings[i] != NULL; i++) {
        strcpy(result + offset, strings[i]);
        offset += strlen(strings[i]);
    }
    return result;
}

int execute_fork(int ac, char **av, char **env, Hello_t *gogo)
{
    char *concatenated;

    if (my_strcmp2(gogo->args[0], "env") == 55 ||
        my_strcmp2(gogo->args[0], "setenv") == 55 ||
        my_strcmp2(gogo->args[0], "unsetenv") == 55)
        return all_env(ac, av, env, gogo);
    if (my_strcmp2(gogo->args[0], "cd") == 55)
        return build_cd(gogo, env);
    concatenated = concatenate_strings(gogo->args);
    if (system(concatenated) != -1) {
        if (isatty(0) != 1)
            exit(0);
        gogo->executed = 1;
    }
    gogo->pid = fork();
    if (gogo->pid == 0) {
        if (gogo->executed == 0)
            suite(gogo, env);
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
