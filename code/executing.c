/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** executing.c
*/

#include "my.h"

static ssize_t check_uf_null(ssize_t chars_read, int fd, char *line)
{
    chars_read = read(fd, line, 1);
    if (chars_read > 0 && (line[0] == ';' || line[0] == '\n')) {
        while (chars_read > 0 && (line[0] == ';' || line[0] == '\n')) {
            chars_read = read(fd, line, 1);
        }
    }
}

static int condition(size_t len, size_t bufsize, char *line)
{
    char *temp = NULL;

    if (len >= bufsize) {
        bufsize += 128;
        temp = malloc(bufsize * sizeof(char));
        line = temp;
    }
    return 0;
}

char *getline_custom(char delim, char delim2)
{
    size_t bufsize = 128;
    char *line = malloc(bufsize * sizeof(char));
    ssize_t len = 0;
    ssize_t chars_read = 0;
    int fd = open(STDIN, O_RDONLY);
    char del;

    chars_read = check_uf_null(chars_read, fd, line);
    while (chars_read > 0) {
        del = line[len];
        if (del == delim || del == delim2)
            break;
        len++;
        condition(len, bufsize, line);
        chars_read = read(fd, line + len, 1);
    }
    line[len] = '\0';
    return line;
}

int parsing_input(Hello_t *gogo)
{
    char *input = malloc(sizeof(char) * 64);
    size_t input_size = 0;

    if (!isatty(0) == 1) {
        input = getline_custom(';', '\n');
    } else {
        gogo->input_length = getline(&input, &input_size, stdin);
    }
    if (input_size == -1)
        return 9;
    if (input[gogo->input_length - 1] == '\n') {
        input[gogo->input_length - 1] = '\0';
    } else {
        gogo->input_length++;
    }
    gogo->i = 0;
    gogo->token = strtok(input, " \t\n");
    return 0;
}
