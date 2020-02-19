/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:12 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/19 16:23:31 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static int	decide_tile_color(t_game_tile *game_tile)
{
	if (game_tile->value == 0 || game_tile->value == 3 || game_tile->value == 4 || game_tile->value == 5 || game_tile->value == 6)
	{
		return (0x00FF0000);
	}
	else if (game_tile->value == 1)
	{
		return (0x00FF7777);
	}
	return (0x00FF0000);
}

static void	spawn_player(t_game_manager *game_manager, t_game_tile *game_tile)
{
	game_manager->player_tile = game_tile;
	game_manager->player_x = (game_tile->start_x + (game_tile->start_x + game_manager->tile_width)) / 2;
	game_manager->player_y = (game_tile->start_y + (game_tile->start_y + game_manager->tile_height)) / 2;
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
			my_mlx_pixel_put(game_manager, x, y, decide_tile_color(game_tile)); //pick color	
			x++;
		}
		x = game_tile->start_x;
		y++;
	}
	mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
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
	int x = 0;
	int y = game_manager->tile_height;

	while (y < game_manager->file_data->resolution[0][1])
	{
		while (x < game_manager->file_data->resolution[0][0])
		{
			my_mlx_pixel_put(game_manager, x, y, 0x0000FF);
			x++;
		}
		x = 0;
		y = y + game_manager->tile_height;
	}
	x = game_manager->tile_width;
	y = 0;
	while (x < game_manager->file_data->resolution[0][0])
	{
		while (y < game_manager->file_data->resolution[0][1])
		{
			my_mlx_pixel_put(game_manager, x, y, 0x0000FF);
			y++;
		}
		y = 0;
		x = x + game_manager->tile_width;
	}
	mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
}