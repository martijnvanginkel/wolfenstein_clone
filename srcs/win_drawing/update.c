/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/20 16:26:23 by mvan-gin      ########   odam.nl         */
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

// void            my_image_put(t_data *img_data, int x, int y, t_data *img_data2)
// {
//     char    *dst;
// 	char	*dst2;

//     dst = img_data->addr + (y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
// 	dst2 = img_data2->addr + (y * img_data2->line_length + x * (img_data2->bits_per_pixel / 8));

// 	*(unsigned int *)dst2 = *(unsigned int *)dst;
// }



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

	// int x = 0;
	// int y = 0;

	// while (y < 100)
	// {
	// 	while (x < 100)
	// 	{
	// 		my_image_put(game_manager.textures->south_tex, x, y, game_manager.world_image);
	// 		x++;
	// 	}
	// 	x = 0;
	// 	y++;
	// }




	mlx_put_image_to_window(world_image.mlx, world_image.mlx_win, world_image.img, 0, 0);


	mlx_hook(game_manager.world_image->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    mlx_loop(game_manager.map_image->mlx);
	mlx_loop(game_manager.world_image->mlx);
}
