/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/25 12:32:34 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

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
	else if (keycode == 12)
		quit_game(game_manager);
	return (0);
}

void	run_game(t_file_data *file_data)
{
    t_data  map_image;
	t_data	world_image;
	t_game_manager game_manager;

	map_image = setup_image_data(file_data);
	world_image = setup_image_data(file_data);

	game_manager.world_image = &world_image; // temp;

	game_manager = setup_game_manager(file_data, &map_image, &world_image);
	draw_map(&game_manager);
	draw_grid(&game_manager);

	get_textures(&game_manager);


	mlx_hook(game_manager.world_image->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    mlx_loop(game_manager.map_image->mlx);
	mlx_loop(game_manager.world_image->mlx);
}
