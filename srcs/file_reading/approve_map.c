/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   approve_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 09:01:13 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/29 16:39:17 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static t_map_tile 	*find_first_tile(t_map_tile **map)
{
	int i;

	i = 0;
	while (map[0][i].value != 1)
		i++;
	return (&(map[0][i]));
}

static int			tile_exists(t_map_tile *tile, t_map_tile **next_tile)
{
	if (tile != NULL && tile->value == 1 && tile->is_visited == 0)
	{
		*next_tile = tile;
		return (1);
	}
	else
		return (0);
}

static t_map_tile	*find_next_tile(t_map_tile ***map, t_map_tile *cur_tile)
{
	t_map_tile *next_tile;

	if (tile_exists(map[cur_tile->value][cur_tile->value + 1], &next_tile)) /* Tile to the right */
	{
		return (next_tile);
	}
	else if (tile_exists(map[cur_tile->value + 1][cur_tile->value], &next_tile)) /* Tile above */
	{
		return (next_tile);
	}
	else if (tile_exists(map[cur_tile->value - 1][cur_tile->value], &next_tile)) /* Tile under */
	{
		return (next_tile);
	}
	else if (tile_exists(map[cur_tile->value][cur_tile->value - 1], &next_tile)) /* Tile to the left */
	{
		return (next_tile);
	}
	else
		return (NULL);
}

int     approve_map(t_map_tile **map)
{
	t_map_tile *first_tile;
	t_map_tile *current_tile;

	first_tile = find_first_tile(map);
	current_tile = first_tile;
	
	printf("%d", current_tile->y_cord);
	printf("%d\n", current_tile->x_cord);

	




	return (0);
}
