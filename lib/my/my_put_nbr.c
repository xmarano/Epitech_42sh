/*
** EPITECH PROJECT, 2023
** eepf
** File description:
** dsfdsf
*/
#include <stddef.h>
#include "my.h"
#include <unistd.h>

int my_put_nbr(int nb)
{
    if (nb < 0) {
        nb = nb * -1;
    }
    if (nb > 9) {
        my_put_nbr(nb / 10);
        my_put_nbr(nb % 10);
    } else {
        my_putchar(nb + '0');
    }
}
