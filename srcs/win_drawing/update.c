/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/14 10:58:35 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

// void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;

//     dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

static int             get_player_input(int keycode, t_game_manager *game_manager)
{
	if (keycode == 13) // up
		move_player(game_manager, 15);
	else if (keycode == 0) // left
		rotate_player(game_manager, 0.1);
	else if (keycode == 1) // down
		move_player(game_manager, -15);
	else if (keycode == 2) // right
		rotate_player(game_manager, -0.1);
	return (0);
}

void	run_game(t_file_data *file_data)
{
    t_data  img_data;
	t_data img_data2;
	t_game_manager game_manager;

	img_data = setup_image_data(file_data);
	img_data2 = setup_image_data(file_data);

	// game_manager.img_data2 = &img_data2; // temp;

	game_manager = setup_game_manager(file_data, &img_data, &img_data2);
	draw_map(&game_manager);
	draw_grid(&game_manager);

	// draw_floor(&game_manager);

    // return ;

	mlx_hook(game_manager.img_data->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    mlx_loop(game_manager.img_data->mlx);
	mlx_loop(game_manager.img_data2->mlx);
}
