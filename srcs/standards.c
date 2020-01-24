/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   standards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:34:22 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/24 16:15:12 by mvan-gin      ########   odam.nl         */
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

int     same_string(char *s1, char *s2, int length)
{
    int i;

    i = 0;
    while (i < length)
    {
        if (s1[i] != s2[i])
        {
            return (0);
        }
        i++;
    }
    return (1);
}

void    print_string(char *str)
{
    write(1, str, get_strlen(str));
}

void    show_error(char *error_message)
{
    print_string("Error\n");
    print_string(error_message);
}