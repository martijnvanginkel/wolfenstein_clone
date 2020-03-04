/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setup_game.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 12:28:29 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/03/04 09:30:22 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void          fill_tile_line(t_file_data *file_data, t_game_manager *game_manager, int start_height, int y)
{
    int x;
    int start_width;

    x = 0;
    start_width = 0;
    while (x < game_manager->file_data->map_width)
    {
        (game_manager->map)[y][x].start_x = start_width;
        (game_manager->map)[y][x].start_y = start_height;
        start_width = start_width + game_manager->tile_width;

        (game_manager->map)[y][x].value = (file_data->map)[y][x].value;
        (game_manager->map)[y][x].x = (file_data->map)[y][x].x;
        (game_manager->map)[y][x].y = (file_data->map)[y][x].y;
		printf("%d ", game_manager->map[y][x].value);
        x++;
    }
	printf("\n");
}

static t_game_tile	**replace_map(t_file_data *file_data, t_game_manager *game_manager)
{
	int		y;
	int		start_height;
	t_game_tile	**tile_map;

	y = 0;
	start_height = 0;
	tile_map = (t_game_tile **)malloc(sizeof(t_game_tile *) * file_data->map_height + 1);
	if (!tile_map)
		return (0);
    game_manager->map = tile_map;
	while (y < file_data->map_height)
	{
		tile_map[y] = (t_game_tile *)malloc(sizeof(t_game_tile) * file_data->map_width + 1);
		if (!tile_map[y])
			return (0);
        fill_tile_line(file_data, game_manager, start_height, y);
		start_height = start_height + game_manager->tile_height;
		y++;
	}
	return (tile_map);
}

t_data	setup_image_data(t_file_data *file_data)
{
	void    *mlx;
    void    *mlx_win;
    t_data  img;

	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, (file_data->resolution)[0][0], (file_data->resolution)[0][1], "Hello world!");
    img.img = mlx_new_image(mlx, (file_data->resolution)[0][0], (file_data->resolution)[0][1]);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	img.mlx = mlx;
	img.mlx_win = mlx_win;
	return (img);
}

t_game_manager	setup_game_manager(t_file_data *file_data, t_data *img, t_data *img2)
{
	t_game_manager	game_manager;
	int				tile_width;
	int				tile_height;

	tile_width = (file_data->resolution)[0][0] / file_data->map_width;
	tile_height = (file_data->resolution)[0][1] / file_data->map_height;

	if (tile_width > tile_height)
		tile_width = tile_height;
	else
		tile_height = tile_width;
	

	game_manager.tile_width = tile_width;
	game_manager.tile_height = tile_height;
	game_manager.file_data = file_data;

	game_manager.player_tile = 0;
	game_manager.map_image = img;
	game_manager.world_image = img2;

	game_manager.player_dir = M_PI;
	game_manager.x_dir = sin(game_manager.player_dir);
	game_manager.y_dir = cos(game_manager.player_dir);

	game_manager.map = replace_map(file_data, &game_manager);

	return (game_manager);
}