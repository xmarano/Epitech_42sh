/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** main1.c
*/

#include "my.h"

int look_errno(Hello_t *gogo)
{
    if (errno == 8) {
        my_printf("%s: "ARCHI, gogo->args[0]);
        exit(55);
    }
}

static int prompt(void)
{
    char current_dir[BUFFER_SIZE];

    my_printf("-> Minishell--");
    getcwd(current_dir, sizeof(current_dir));
    my_printf("\033[34;01m%s\033[00m -> ", current_dir);
}

int main(int ac, char **av, char **env)
{
    Hello_t gogo;

    definition(&gogo);
    if (ac >= 2)
        return 84;
    if (isatty(0) == 1)
        prompt();
    return mini_shell(ac, av, env, &gogo);
}
