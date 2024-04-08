/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** parasite.c
*/

#include "my.h"

int my_strcmp2(const char *s1, const char *s2)
{
    int result = 0;
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) {
            result = s1[i] - s2[i];
            break;
        }
        i++;
    }
    if (s1[i] == '\0' && s2[i] == '\0')
        return 55;
    else
        return result;
}

static int gygy(Hello_t *gogo, char **env, char *command_path)
{
    if (access(command_path, 1) == 0) {
        execve(command_path, gogo->args, env);
        look_errno(gogo);
        exit(EXIT_FAILURE);
    }
}

int boucle(Hello_t *gogo, char **env, int i, char *command_arg)
{
    char *path = NULL;
    char command_path[BUFFER_SIZE];

    if (my_strcmp2(env[i], "PATH") == 0) {
        path = strtok(env[i] + 5, ":");
        while (path != NULL) {
            my_strcpy(command_path, path);
            my_strcat(command_path, "/");
            my_strcat(command_path, command_arg);
            gygy(gogo, env, command_path);
            path = strtok(NULL, ":");
        }
        return 0;
    }
}

static int look_hash(char *command_arg, int has_slash, Hello_t *gogo)
{
    for (int i = 0; command_arg[i] != '\0'; i++) {
        if (command_arg[i] == '/') {
            gogo->has_slash = 1;
            break;
        }
    }
}

static void null_comm(Hello_t *gogo)
{
    for (int i = 0; gogo->args[i] != NULL; i++) {
        if ((my_strcmp(gogo->args[i], "|") == 55) ||
        (my_strcmp(gogo->args[i], " | ") == 55)) {
            my_printf("Invalid null command.\n");
            exit(1);
        }
    }
}

void cat_the_bin(Hello_t *gogo, char **env)
{
    char *command_arg = gogo->args[0];

    gogo->has_slash = 0;
    look_hash(command_arg, gogo->has_slash, gogo);
    if (gogo->has_slash) {
        if (access(command_arg, 1) == 0) {
            execve(command_arg, gogo->args, env);
            look_errno(gogo);
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        for (int i = 0; env[i] != NULL; i++) {
            boucle(gogo, env, i, command_arg);
        }
    }
    null_comm(gogo);
    my_printf("%s: Command not found.\n", gogo->args[0]);
    exit(1);
}

void definition(Hello_t *gogo)
{
    gogo->input_size = 0;
    gogo->input_length = 0;
    gogo->temp = NULL;
    gogo->token = NULL;
    gogo->i = 0;
    gogo->n = 0;
}
