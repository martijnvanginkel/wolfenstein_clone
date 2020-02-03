/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   approve_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 09:01:13 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/03 12:59:50 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_map_tile	*find_first_tile(t_map_tile **map)
{
	int i;

	i = 0;
	while (map[0][i].value != 1)
		i++;
	return (&(map[0][i]));
}

static int			tile_exists(t_map_tile *tile)
{
	if (tile == 0)
		return (0);
	if (tile != NULL && tile->value == 1 && tile->is_visited == 0)
		return (1);
	else
		return (0);
}

static t_map_tile	*fill_old_return_new(t_map_tile *old_tile, t_map_tile *new_tile, t_map_tile *first_tile)
{
	if (old_tile != first_tile)
		old_tile->is_visited = 1;

	new_tile->previous_tile = old_tile;
	return (new_tile);
}

static t_map_tile	*find_next_tile(t_map_tile **map, t_map_tile *cur_tile,
								t_map_tile *first_tile, t_file_data *file_data)
{
	t_map_tile *next_tile;
	
	next_tile = 0;
	if (cur_tile->x < file_data->map_width - 1 && tile_exists(&(map[cur_tile->y][cur_tile->x + 1]))) /* Tile to the right */
	{
		next_tile = &(map[cur_tile->y][cur_tile->x + 1]);
	}	
	else if (cur_tile->y > 0 && tile_exists(&(map[cur_tile->y - 1][cur_tile->x]))) /* Tile above */
	{
		next_tile = &(map[cur_tile->y - 1][cur_tile->x]);
	}
	else if (cur_tile->y < file_data->map_height - 1 && tile_exists(&(map[cur_tile->y + 1][cur_tile->x]))) /* Tile under */
	{
		next_tile = &(map[cur_tile->y + 1][cur_tile->x]);	
	}
	else if (cur_tile->x > 0 && tile_exists(&(map[cur_tile->y][cur_tile->x - 1]))) /* Tile to the left */
	{
		next_tile = &(map[cur_tile->y][cur_tile->x - 1]);
	}
	else
	{
		cur_tile->is_visited = 1;
		next_tile = cur_tile->previous_tile;
		if (next_tile->previous_tile == first_tile) /* If it's stuck and it goes back to the first_tile, set is_visited to 1 so its marked that the map didn't loop around */
		{
			(next_tile->previous_tile)->is_visited = 1;
			return (next_tile->previous_tile);
		}
		return (next_tile);
	}

	return (fill_old_return_new(cur_tile, next_tile, first_tile));
}

int					approve_map(t_map_tile **map, t_file_data *file_data)
{
	t_map_tile *first_tile;
	t_map_tile *current_tile;

	first_tile = find_first_tile(map);
	current_tile = first_tile;
	current_tile = find_next_tile(map, current_tile, first_tile, file_data);
	if (!current_tile)
		return (0);
	while (current_tile != first_tile)
	{
		current_tile = find_next_tile(map, current_tile, first_tile, file_data);
		if (!current_tile)
			return (0);
		if (current_tile == first_tile)
		{
			if (current_tile->is_visited == 1) /* Went back from where it came, failed */
			{
				printf("\nFail: looped back\n");
				return (0);
			}
			else /* It looped around till the first_tile, success */
			{
				printf("\nSuccess: looped around\n");
				return (1);
			}
		}
		printf("[%d][%d]\n", current_tile->y, current_tile->x);
	}

	return (0);
}
