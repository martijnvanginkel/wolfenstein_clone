/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   approve_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 09:01:13 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/23 11:31:02 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int     check_outer_line(int *column)
{
    int index;

    index = 0;
    while (column[index] != -1)
    {
        if (column[index] != 1)
        {
            return (0);
        }
        index++;
    }
    return (1);
}

int     check_inner_line(int *column)
{
    int index;

    index = 0;
    while (column[index] != -1)
    {
        if (index == 0 || column[index + 1] == -1) /* First or last one of every column */
        {
            if (column[index] != 1)
            {
                return (0);
            }
        }
        index++;
    }
    return (1);
}

int     approve_map(int **map, int height)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < height)
    {
        if (y == 0 || y == (height - 1))
        {
            if (!check_outer_line(map[y]))
                return (0);
        }
        else
        {
            if (!check_inner_line(map[y]))
                return (0);
        }
        
        y++;
    }
    return (1);
}
