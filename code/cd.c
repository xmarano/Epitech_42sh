/*
** EPITECH PROJECT, 2023
** B-PSU-200-MAR-2-1-minishell2-yanis.prevost
** File description:
** cd.c
*/

#include "my.h"

static void forbomb(char **env, int i, int *j)
{
    for (*j = 0; env[i][*j] != '='; (*j)++) {
    }
}

static int next_cd(Hello_t *gogo, char **env)
{
    char *old_dir = malloc(sizeof(char) * 100);
    int j;

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strcmp2(env[i], "OLDPWD") == 0) {
            forbomb(env, i, &j);
            my_strcpy(old_dir, env[i] + j + 1);
            break;
        }
    }
    if (my_strcmp2(gogo->args[1], "--") == 55) {
        chdir("/");
        return 0;
    }
    if (gogo->args[1][0] == '-') {
        chdir(old_dir);
        return 0;
    }
}

int build_cd(Hello_t *gogo, char **env)
{
    if (gogo->args[1] == NULL || gogo->args[1][0] == '~') {
        chdir("/");
        return 0;
    }
    if (my_strcmp(gogo->args[1], "--") == 55)
        return next_cd(gogo, env);
    if (chdir(gogo->args[1]) != 0) {
        my_printf("%s: Not a directory.\n", gogo->args[1]);
        return ex_or_rt();
    }
}
