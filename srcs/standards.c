/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   standards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:34:22 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/27 12:57:08 by mvan-gin      ########   odam.nl         */
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

int     empty_till_n(char *str, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        if (str[i] == '\n')
            return (1);
        else if (str[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}

int     is_empty_line(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0' && str[i] != '\n')
    {
        if (str[i] != ' ' || str[i] != '\t')
        {
            return (0);
        }
        i++;   
    }
    return (1);
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