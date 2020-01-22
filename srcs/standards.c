/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   standards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:34:22 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/22 16:47:21 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char    *make_empty_string()
{
    char *str;

    str = malloc(sizeof(char) * 1);
    if (!str)
        return (0);
    str[0] = '\0';
    return (str);
}

int     find_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}

void    print_string(char *str)
{
    write(1, str, find_strlen(str));
}