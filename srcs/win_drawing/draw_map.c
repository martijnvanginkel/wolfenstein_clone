/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:12 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/28 14:47:31 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void	spawn_player(t_game_manager *game_manager, t_game_tile *game_tile)
{
	game_manager->player_tile = game_tile;
	game_manager->player_x = (float)game_tile->x + 0.5;
	game_manager->player_y = (float)game_tile->y + 0.5;
}

static void	draw_tile(t_game_tile *game_tile, t_game_manager *game_manager)
{
	int x = game_tile->start_x;
	int y = game_tile->start_y;

	if (game_tile->value == 3 || game_tile->value == 4 || game_tile->value == 5 || game_tile->value == 6)
		spawn_player(game_manager, game_tile);
	while (y < (game_tile->start_y + game_manager->tile_height))
	{
		while (x < (game_tile->start_x + game_manager->tile_width))
		{
			x++;
		}
		x = game_tile->start_x;
		y++;
	}
}

void    draw_map(t_game_manager *game_manager)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < game_manager->file_data->map_height)
	{
		while (x < game_manager->file_data->map_width)
		{
			draw_tile(&(game_manager->map[y][x]), game_manager);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_grid(t_game_manager *game_manager)
{

}