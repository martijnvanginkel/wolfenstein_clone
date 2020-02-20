/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/20 11:50:59 by mvan-gin      ########   odam.nl         */
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
	return (0);
}

t_texture_images	*setup_textures(t_game_manager *game_manager)
{

}



void            my_image_put(t_data *img_data, int x, int y, t_data *img_data2)
{
    char    *dst;
	char	*dst2;

    dst = img_data->addr + (y * img_data->line_length + x * (img_data->bits_per_pixel / 8));
	dst2 = img_data2->addr + (y * img_data2->line_length + x * (img_data2->bits_per_pixel / 8));

	*(unsigned int *)dst2 = *(unsigned int *)dst;
}


void	run_game(t_file_data *file_data)
{
    t_data  img_data;
	t_data img_data2;
	t_game_manager game_manager;

	img_data = setup_image_data(file_data);
	img_data2 = setup_image_data(file_data);

	game_manager.img_data2 = &img_data2; // temp;

	game_manager = setup_game_manager(file_data, &img_data, &img_data2);
	draw_map(&game_manager);
	draw_grid(&game_manager);



    t_data  img;
	int		img_width;
	int		img_height;

	img.mlx = mlx_init();
    img.img = mlx_png_file_to_image(img.mlx, "srcs/sprites/wood.png", &img_width, &img_height);
	if (img.img == NULL)
	{
		printf("failed reading\n");
		return ;
	}
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.mlx_win = img_data2.mlx_win;

	int x = 0;
	int y = 0;

	while (y < 100)
	{
		while (x < 100)
		{
			my_image_put(&img, x, y, &img_data2);
			x++;
		}
		x = 0;
		y++;
	}




	mlx_put_image_to_window(img_data2.mlx, img_data2.mlx_win, img_data2.img, 0, 0);


	mlx_hook(game_manager.img_data->mlx_win, 2, 1L<<0, get_player_input, &game_manager);

    mlx_loop(game_manager.img_data->mlx);
	mlx_loop(game_manager.img_data2->mlx);
}
