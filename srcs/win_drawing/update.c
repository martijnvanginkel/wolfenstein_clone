/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/06 13:03:14 by mvan-gin      ########   odam.nl         */
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

int             get_player_input(int keycode, t_game_manager *game_manager)
{
   	// printf("pressed: %d\n", keycode);
	// double dir = M_PI;

	// printf("dir_value;%d\n", dir);

	// printf("%f\n", cos(1));
	// printf("%f\n", sin(1));


	if (keycode == 13) // up
	{
		//update_player(game_manager, 0, -10);
	}
	else if (keycode == 0) // left
	{
		game_manager->player_dir = (game_manager->player_dir - 0.05);
		// game_manager->x_dir = cos(game_manager->player_dir);
		// game_manager->y_dir = sin(game_manager->player_dir);


		printf("pd: %f\n", game_manager->player_dir);

		// float x = game_manager->x_dir;
		// float y = game_manager->y_dir;
		int i = 0;
		printf("x_dir: %f\n", game_manager->x_dir);
		printf("y_dir: %f\n", game_manager->y_dir);
		double x = game_manager->player_x;
		double y = game_manager->player_y;
		double x1 = sin(game_manager->player_dir);
		double y1 = cos(game_manager->player_dir);

		// while (i < 10)
		// {
			// game_manager->player_x = (game_manager->player_x + (1 * game_manager->x_dir));
			// game_manager->player_y = (game_manager->player_y + (1 * game_manager->y_dir));


		while (i < 50)
		{
			my_mlx_pixel_put(game_manager->img_data, x, y, 0x000000);

			x += x1;
			y += y1;
			i++;
		}
		

		
		mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
	}
	else if (keycode == 1) // down
	{
		//update_player(game_manager, 0, 10);
	}
	else if (keycode == 2) // right
	{
		game_manager->player_dir = (game_manager->player_dir + 0.05);
		game_manager->x_dir = cos(game_manager->player_dir);
		game_manager->y_dir = sin(game_manager->player_dir);


		printf("pd: %f\n", game_manager->player_dir);
		printf("x_dir: %f\n", game_manager->x_dir);
		printf("y_dir: %f\n", game_manager->y_dir);
	}


	// update_player(game_manager);
	// draw_player(game_manager);
	return (0);
}

// 1 radian = 57 degrees

void	draw_line(t_game_manager *game_manager)
{
	// static double dir = M_PI;

	// printf("%f\n", cos(1));
	// printf("%f\n", sin(1));



}

void	run_game(t_file_data *file_data)
{
    t_data  img_data;
	t_game_manager game_manager;

	img_data = setup_image_data(file_data);
	game_manager = setup_game_manager(file_data, &img_data);


	draw_map(&game_manager);


	//draw_line(&game_manager);

	// return ;
	// draw_player(&game_manager);


	mlx_hook(game_manager.img_data->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    // mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(game_manager.img_data->mlx);
}
