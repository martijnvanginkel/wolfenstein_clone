/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/05 17:23:40 by mvan-gin      ########   odam.nl         */
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
   	printf("pressed: %d\n", keycode);
	if (keycode == 13) // up
	{
		update_player(game_manager, 0, -10);
	}
	else if (keycode == 0) // left
	{



		//update_player(game_manager, -10, 0);
	}
	else if (keycode == 1) // down
	{
		//update_player(game_manager, 0, 10);
	}
	else if (keycode == 2) // right
	{
		//update_player(game_manager, 10, 0);
	}
	// update_player(game_manager);
	// draw_player(game_manager);
	return (0);
}

void	draw_circle(int x_centre, int y_centre, int r)
{


    // return 0;

}

void	draw_line(t_game_manager *game_manager)
{

    int radius = 160;
	int i = 0;
	int j = 0;
	while (i <= 2*radius)
	{
		while (j <= 2*radius)
		{
            double distance = sqrt((double)(i-radius)*(i-radius) + (j-radius)*(j-radius));
            if (distance>radius-0.5 && distance<radius+0.5)
            {
                my_mlx_pixel_put(game_manager->img_data, i, j, 0x000000);
            }

			j++;
		}
		j = 0;
		i++;
	}


  
        // for (j=0; j<=2*radius; j++)
        // {
        //     double distance = sqrt((double)(i-radius)*(i-radius) + (j-radius)*(j-radius));
        //     if (distance>radius-0.5 && distance<radius+0.5)
        //     {
        //         my_mlx_pixel_put(game_manager->img_data, i, j, 0x000000);
        //     }

        // }


	// draw_circle(100, 100, 30);

	// while (y < 150)
	// {
	// 	my_mlx_pixel_put(game_manager->img_data, game_manager->player_x + y, game_manager->player_y, 0x000000);
	// 	y++;
	// }
}

void	run_game(t_file_data *file_data)
{
    t_data  img_data;
	t_game_manager game_manager;

	img_data = setup_image_data(file_data);
	game_manager = setup_game_manager(file_data, &img_data);


	draw_map(&game_manager);
	draw_line(&game_manager);
	//draw_player(&game_manager);


	mlx_hook(game_manager.img_data->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    // mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(game_manager.img_data->mlx);
}
