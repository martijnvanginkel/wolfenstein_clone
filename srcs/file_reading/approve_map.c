/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   approve_map.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/23 09:01:13 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/30 11:14:33 by mvan-gin      ########   odam.nl         */
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

static int			tile_exists(t_map_tile *next_tile)
{
	if (next_tile == 0)
		return (0);
	if (next_tile != NULL && next_tile->value == 1 && next_tile->is_visited == 0)
	{		
		return (1);
	}
	else
		return (0);
}

/* Return the new tile and set changes to the old tile */
static t_map_tile	*fill_old_return_new(t_map_tile *old_tile, t_map_tile *new_tile)
{
	old_tile->is_visited = 1;
	new_tile->previous_tile = old_tile;
	return (new_tile);
}

static t_map_tile	*find_next_tile(t_map_tile **map, t_map_tile *cur_tile, int height)
{
	t_map_tile *next_tile;

	next_tile = 0;
	if (tile_exists(&(map[cur_tile->y][cur_tile->x + 1]))) /* Tile to the right */
	{
		next_tile = &(map[cur_tile->y][cur_tile->x + 1]);
		printf("right\n");
	}		
	else if (cur_tile->y > 0 && tile_exists(&(map[cur_tile->y - 1][cur_tile->x]))) /* Tile above */
	{
		next_tile = &(map[cur_tile->y - 1][cur_tile->x]);
		printf("up\n");
	}
	else if (cur_tile->y < height - 1 && tile_exists(&(map[cur_tile->y + 1][cur_tile->x]))) /* Tile under */
	{
		next_tile = &(map[cur_tile->y + 1][cur_tile->x]);
		printf("down\n");
	}	
	else if (cur_tile->x > 0 && tile_exists(&(map[cur_tile->y][cur_tile->x - 1]))) /* Tile to the left */
	{
		next_tile = &(map[cur_tile->y][cur_tile->x - 1]);
		printf("left\n");
	}
	else
	{
		cur_tile->is_visited = 1;
		next_tile = cur_tile->previous_tile;
		printf("going back\n");
		return (next_tile);
		// return (0);
	}
	
	return (fill_old_return_new(cur_tile, next_tile));
}

int     approve_map(t_map_tile **map, int height)
{
	t_map_tile *first_tile;
	t_map_tile *current_tile;

	int loop = 0;

	first_tile = find_first_tile(map);
	current_tile = first_tile;

	printf("%d\n", current_tile->y);
	printf("%d\n", current_tile->x);

	while (loop < 80)
	{
		current_tile = find_next_tile(map, current_tile, height);
		if (!current_tile)
			return (0);
		if (loop == 0)
			first_tile->is_visited = 0;
			
		if (current_tile == first_tile)
		{
			printf("\nback on first tile\n");
			return (0);
		}


		printf("%d\n", current_tile->y);
		printf("%d\n", current_tile->x);
		loop++;
	}

	printf("%d", map[0][7].is_visited);
	

	return (0);
}
