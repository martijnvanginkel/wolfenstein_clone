/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 14:58:12 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/24 19:06:57 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int     fill_map_tile(int *map_tile, char *str, int *index, int *x)
{
    static int spawned_player = 0;

    if (str[*index] >= '0' && str[*index] <= '2')
        *map_tile = str[*index] - 48;
    else if (spawned_player == 0)
    {
        if (str[*index] == 'N')
            *map_tile = 3;
        else if (str[*index] == 'S')
            *map_tile = 4;
        else if (str[*index] == 'E')
            *map_tile = 5;
        else if (str[*index] == 'W')
            *map_tile = 6; 
        else
            return (0);
        spawned_player = 1;
    }
    else
        return (0);
    *index = *index + 2;
    (*x)++;
    return (1);
}

/* Fills in the pointer to the 2D array */
int    fill_map(int ***map, int height, char *content_string)
{
    int x;
    int y;
    int index;
    int width;

    x = 0;
    y = 0;
    index = 0;
    while (y < height && content_string[index] != '\0')
    {
        width = get_map_width(content_string, index);
        (*map)[y] = (int *)malloc(sizeof(int) * (width + 1)); /* One more for the -1 at the end of each column */
        if (!(*map)[y])
            return (0);
        while (x < width)
        {
            if (!fill_map_tile(&(*map)[y][x], content_string, &index, &x))
                return (0);
        }
        (*map)[y][x] = -1; /* Put a -1 at the end of every column */
        x = 0;
        y++;
    }
    return (1);
}

int     **allocate_map(char *content_string)
{
    int **map;
    int height;

    height = get_map_height(content_string);
    map = (int **)malloc(sizeof(int *) * (height + 1));
    if (!map)
        return (0);
    if (!fill_map(&map, height, content_string))
        return (0);
    if (!approve_map(map, height))
        return (0);

    /* this is to recognize when to stop for the free_map function */
    map[height] = 0;
    
    print_map(map, height);
    return (map);
}