/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 19:04:55 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/24 19:05:25 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void    print_map(int **map, int height)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < height)
    {
        while (map[y][x] != -1)
        {
            printf("%d ", map[y][x]);
            x++;
        }
        printf("\n");
        x = 0;
        y++;
    }
}

void    free_map(int **map)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (map[y] != 0)
    {
        free(map[y]);
        y++;
    }
    free(map);
}

int     get_map_height(char *content_string)
{
    int i;
    int height;

    i = 0;
    height = 0;
    while (content_string[i] != '\0')
    {
        if (content_string[i] == '\n')
        {
            height++;
        }
        i++;
    }
    height++;
    return (height);
}

int     get_map_width(char *content_string, int index)
{
    int width;

    width = 0;
    while (content_string[index] != '\0')
    {
        if (content_string[index] == '\n')
        {
            width = (width / 2) + 1;
            return (width);
        }
        index++;
        width++;
    }
    width = (width / 2) + 1;
    return (width);
}