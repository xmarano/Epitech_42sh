/*
** EPITECH PROJECT, 2023
** test_my_ls
** File description:
** my_strcmp.c
*/
#include "my.h"
#include <stdio.h>

int my_strcmp(const char *s1, const char *s2)
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
    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    } else {
        return 55;
    }
}
