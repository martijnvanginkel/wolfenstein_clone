/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   standards.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:34:22 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/28 17:46:49 by mvan-gin      ########   odam.nl         */
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

int         str_to_number(int *num_ptr, char *file_string, int *index)
{
    *num_ptr = 0;
    while (file_string[*index] >= '0' && file_string[*index] <= '9')
    {
        *num_ptr = *num_ptr * 10 + (file_string[*index] - 48);
        (*index)++;
    }
    return (*num_ptr);
}

int     is_empty_line(char *str, int index)
{
    int i;

    i = 0;
    while (str[index] != '\0' && str[index] != '\n')
    {
        if (str[index] != ' ' && str[index] != '\t')
        {
            return (0);
        }
        index++;   
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