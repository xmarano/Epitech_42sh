/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** env.c
*/

#include "my.h"

int ex_or_rt(void)
{
    if (isatty(0) == 1)
        return 1;
    else
        exit(1);
}

static int boucle(char **env, int i)
{
    while (env[i] != NULL) {
        env[i] = env[i + 1];
        i++;
    }
}

int build_unsetenvenv(char **env, Hello_t *gogo)
{
    int size = my_strlen(gogo->args[1]);

    for (int i = 0; env[i] != NULL; i++) {
        if (my_strcmp(env[i], gogo->args[1]) == 55 && env[i][size] == '=') {
            boucle(env, i);
            break;
        }
    }
}

static void boucle_find(char **env, Hello_t *gogo, char *cat_value, int size)
{
    int i = 0;

    for (i = 0; env[i] != NULL; i++) {
        if (my_strcmp(env[i], gogo->args[1]) == 55 && env[i][size] == '=') {
            env[i] = cat_value;
            return;
        }
    }
    env[i] = cat_value;
    env[i + 1] = NULL;
    return;
}

int build_setenv(char **env, Hello_t *gogo)
{
    int size = my_strlen(gogo->args[1]);
    char *cat_value = NULL;
    char *temp = (char *)malloc(size + 2);

    if (gogo->args[3] == NULL) {
        my_strcpy(temp, gogo->args[1]);
        my_strcat(temp, "=");
        if (gogo->args[2] != NULL)
            cat_value = my_strcat(temp, gogo->args[2]);
        else
            cat_value = temp;
        boucle_find(env, gogo, cat_value, size);
    }
    return 0;
}

static int gest(Hello_t *gogo, char **env)
{
    char *arg = gogo->args[1];

    while (*arg) {
        if (*arg >= '0' && *arg <= '9') {
            my_printf("setenv: Variable name must begin with a letter.\n");
            return ex_or_rt();
        }
        if (*arg == '=') {
            my_printf(ERR);
            return ex_or_rt();
        }
        arg++;
    }
    if (gogo->args[3] != NULL) {
        my_printf("setenv : Too many arguments.\n");
        return ex_or_rt();
    }
}

static int look_unsetenv(Hello_t *gogo, char **env)
{
    if ((my_strcmp(gogo->args[0], "unsetenvenv") == 55)) {
        if (gogo->args[1] == NULL) {
            my_printf("unsetenvenv: Too few arguments.\n");
            return ex_or_rt();
        }
        build_unsetenvenv(env, gogo);
    }
    return 0;
}

static int affichage(Hello_t *gogo, char **env)
{
    for (int i = 0; env[i] != NULL; i++) {
        my_printf("%s\n", env[i]);
    }
    return 0;
}

int all_env(int ac, char **av, char **env, Hello_t *gogo)
{
    if (my_strcmp(gogo->args[0], "env") == 55 && gogo->args[1] == NULL) {
        for (int i = 0; env[i] != NULL; i++) {
            my_printf("%s\n", env[i]);
        }
    }
    look_unsetenv(gogo, env);
    if (my_strcmp(gogo->args[0], "setenv") == 55) {
        if (gogo->args[1] == NULL) {
            affichage(gogo, env);
            return 0;
        }
        if (gest(gogo, env) == 1)
            return 1;
        build_setenv(env, gogo);
    }
    return 0;
}
