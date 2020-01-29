/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 14:58:12 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/29 16:17:16 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void				print_map(t_map_tile **map, int height)
{
	int x = 0;
	int y = 0;

	while (y < height)
	{
		while (map[y][x].value != -1)
		{
			printf("%d ", map[y][x].value);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

static int				set_player_spawn(t_map_tile *tile, char c)
{
	static int spawned_player = 0;

	if (spawned_player == 1)
		return (0);
	if (c == 'N')
		tile->value = 3;
	else if (c == 'S')
		tile->value = 4;
	else if (c == 'E')
		tile->value = 5;
	else if (c == 'W')
		tile->value = 6; 
	else
		return (0);
	spawned_player = 1;
	return (1);
}

static int				fill_map_tile(t_map_tile *tile, char c)
{
	if (c >= '0' && c <= '2')
		tile->value = c - 48;
	else if (c == ' ')
		tile->value = 9;
	else
	{
		if (!set_player_spawn(tile, c))
			return (0);
	}
	tile->is_visited = 0;
	tile->previous_tile = 0;
	return (1);
}

static int				fill_map_line(t_map_tile *tile, char *content_string, int length, int *index)
{
	int x;

	x = 0;
	while (x < length && content_string[*index] != '\0')
	{
		if (!fill_map_tile(&(tile[x]), content_string[*index]))
			return (0);
		(*index) = (*index) + 2;
		x++;
	}
	tile[x].value = -1;
	return (1);
}

static int				fill_map(t_map_tile ***map, int height, char *content_string)
{
	int y;
	int index;
	int width;

	y = 0;
	index = 0;
	while (y < height && content_string[index] != '\0')
	{
		width = get_map_width(content_string, index);
		(*map)[y] = (t_map_tile *)malloc(sizeof(t_map_tile) * width + 1);
		if (!(*map)[y])
			return (0);
		if (!fill_map_line((*map)[y], content_string, width, &index))
			return (0);
        y++;
	}
	return (1);
}

t_map_tile		**get_map(char *content_string)
{
	int			height;
	t_map_tile	**map;

	height = get_map_height(content_string);
	map = (t_map_tile **)malloc(sizeof(t_map_tile *) * (height + 1));
	if (!map)
		return (0);
	if (!fill_map(&map, height, content_string))
		return (0);

	approve_map(map);

	return (0);
}