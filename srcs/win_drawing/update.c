/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/06 15:48:17 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// t_game_tile		*find_game_tile(t_game_manager *game_manager, int x_value, int y_value)
// {
// 	int y = 0;
// 	int x = 0;

// 	while (y < game_manager->file_data->map_height)
// 	{
// 		while (x < game_manager->file_data->map_width)
// 		{
// 			if (x_value >= game_manager->map[y][x].start_x && x_value < game_manager->map[y][x].start_x + game_manager->tile_width &&
// 				y_value >= game_manager->map[y][x].start_y && y_value < game_manager->map[y][x].start_y + game_manager->tile_height)
// 			{
// 				printf("[%d]", game_manager->map[y][x].start_x);
// 				printf("[%d]\n", game_manager->map[y][x].start_y);
// 				printf("[%d]", game_manager->map[y][x].x);
// 				printf("[%d]\n", game_manager->map[y][x].y);
// 				return (&(game_manager->map[y][x]));
// 			}
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// 	return (0);
// }

int             get_player_input(int keycode, t_game_manager *game_manager)
{

	if (keycode == 13) // up
	{
		//update_player(game_manager, 0, -10);
	}
	else if (keycode == 0) // left
	{
		rotate_player(game_manager, -0.05);
	}
	else if (keycode == 1) // down
	{
		//update_player(game_manager, 0, 10);
	}
	else if (keycode == 2) // right
	{
		rotate_player(game_manager, 0.05);
	}


	return (0);
}



void	run_game(t_file_data *file_data)
{
    t_data  img_data;
	t_game_manager game_manager;

	img_data = setup_image_data(file_data);
	game_manager = setup_game_manager(file_data, &img_data);


	draw_map(&game_manager);
	draw_grid(&game_manager);


	mlx_hook(game_manager.img_data->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    mlx_loop(game_manager.img_data->mlx);
}
