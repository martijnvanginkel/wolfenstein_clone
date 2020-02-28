/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/24 14:58:12 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/26 13:42:51 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

static int				fill_map_tile(t_map_tile *tile, char c, int x_cord, int y_cord)
{
	tile->value = 0;
	if (c >= '0' && c <= '2')
		tile->value = c - 48;
	else if (c == ' ')
		tile->value = 0; /* Was 9 before */
	else
	{
		if (!set_player_spawn(tile, c))
			return (0);
	}
	tile->x = x_cord;
	tile->y = y_cord;
	tile->is_visited = 0;
	tile->previous_tile = 0;
	return (1);
}

static int				fill_map_line(t_map_tile *tile, char *content_string, int *index, int y_cord)
{
	int x;

	x = 0;
	while (content_string[*index + 1] != '\n' && content_string[*index + 1] != '\0')
	{
		fill_map_tile(&(tile[x]), content_string[*index], x, y_cord);
		(*index) = (*index) + 2;
		x++;
	}
	fill_map_tile(&(tile[x]), content_string[*index], x, y_cord);
	(*index) = (*index) + 2;
	x++;
	while (tile[x].value != -1)
	{
		fill_map_tile(&(tile[x]), ' ', x, y_cord);
		x++;
	}
	return (1);
}

static int				fill_map(t_map_tile ***map, t_file_data *file_data, char *content_string)
{
	int y;
	int x;
	int index;

	y = 0;
	x = 0;
	index = 0;
	while (y < file_data->map_height && content_string[index] != '\0')
	{
		(*map)[y] = (t_map_tile *)malloc(sizeof(t_map_tile) * file_data->map_width);
		if (!(*map)[y])
			return (0);
		(*map)[y][file_data->map_width].value = -1;
		if (!fill_map_line((*map)[y], content_string, &index, y))
			return (0);
		printf("\n");
        y++;
	}
	return (1);
}

t_map_tile		**get_map(t_file_data *file_data, int index)
{
	t_map_tile	**map;

	file_data->map_height = get_map_height(&(file_data->full_file)[index]);
	file_data->map_width = get_widest_map_line(file_data->full_file, index);
	map = (t_map_tile **)malloc(sizeof(t_map_tile *) * (file_data->map_height + 1));
	if (!map)
		return (0);
	if (!fill_map(&map, file_data, &(file_data->full_file)[index]))
		return (0);
	if (!approve_map(map, file_data))
		return (0);
	return (map);
}
