/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/31 11:53:37 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/31 15:39:34 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct 	s_game_tile
{
	int			value;
	int			x;
	int			y;
	int			start_x;
	int			start_y;
}				t_game_tile;

typedef struct	s_game_manager
{
	t_game_tile		**map;
	int				map_height;
	int				map_width;
	int				tile_width;
	int				tile_height;

	t_game_tile		*player_tile;
	int				player_x;
	int				player_y;

	void			*mlx;
    void			*win;
	t_data  		*img;
}				t_game_manager;


void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static t_game_tile	**replace_map(t_file_data *file_data, int tile_width, int tile_height)
{
	int		x;
	int		y;
	int		start_width;
	int		start_height;
	t_game_tile	**tile_map;


	x = 0;
	y = 0;
	start_width = 0;
	start_height = 0;
	tile_map = (t_game_tile **)malloc(sizeof(t_game_tile *) * file_data->map_height + 1);
	if (!tile_map)
		return (0);
	while (y < file_data->map_height)
	{
		tile_map[y] = (t_game_tile *)malloc(sizeof(t_game_tile) * file_data->map_width + 1);
		if (!tile_map[y])
			return (0);
		while (x < file_data->map_width)
		{
			tile_map[y][x].start_x = start_width;
			tile_map[y][x].start_y = start_height;
			start_width = start_width + tile_width;

			tile_map[y][x].value = (file_data->map)[y][x].value;
			tile_map[y][x].x = (file_data->map)[y][x].x;
			tile_map[y][x].y = (file_data->map)[y][x].y;
			x++;
		}
		start_height = start_height + tile_height;
		start_width = 0;
		x = 0;
		y++;
	}


	x = 0;
	y = 0;
	while (y < file_data->map_height)
	{
		while (x < file_data->map_width)
		{
			printf("[%d] [%d]\n", tile_map[y][x].start_y, tile_map[y][x].start_x);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}

	return (tile_map);
}

static t_game_manager	setup_game_manager(t_file_data *file_data)
{
	t_game_manager	game_manager;
	int				tile_width;
	int				tile_height;

	tile_width = (file_data->resolution)[0][0] / file_data->map_width;
	tile_height = (file_data->resolution)[0][1] / file_data->map_height;
	game_manager.tile_width = tile_width;
	game_manager.tile_height = tile_height;
	game_manager.map_width = file_data->map_width;
	game_manager.map_height = file_data->map_height;
	game_manager.map = replace_map(file_data, tile_width, tile_height);
	game_manager.player_tile = 0;
	return (game_manager);
}

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
}

static void	spawn_player(t_game_manager *game_manager, t_game_tile *game_tile)
{
	game_manager->player_tile = game_tile;
	game_manager->player_x = (game_tile->start_x + (game_tile->start_x + game_manager->tile_width)) / 2;
	game_manager->player_y = (game_tile->start_y + (game_tile->start_y + game_manager->tile_height)) / 2;
}

static void	draw_tile(t_game_tile *game_tile, t_game_manager *game_manager, t_data img)
{
	int x = game_tile->start_x;
	int y = game_tile->start_y;

	if (game_tile->value == 3 || game_tile->value == 4 || game_tile->value == 5 || game_tile->value == 6)
	{
		spawn_player(game_manager, game_tile);
		// game_manager->player_tile = game_tile;
	}

	while (y < (game_tile->start_y + game_manager->tile_height))
	{
		while (x < (game_tile->start_x + game_manager->tile_width))
		{
			my_mlx_pixel_put(&img, x, y, decide_tile_color(game_tile)); //pick color
			x++;
		}
		x = game_tile->start_x;
		y++;
	}

}

static void draw_map(t_game_manager *game_manager, t_data img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < game_manager->map_height)
	{
		while (x < game_manager->map_width)
		{
			draw_tile(&(game_manager->map[y][x]), game_manager, img);
			x++;
		}
		x = 0;
		y++;
	}

	printf("x3:%d\n", (game_manager->player_tile)->x);
}



typedef struct	s_vars
{
        void    *mlx;
        void    *win;
}				t_vars;

int             player_input(int keycode, t_game_manager *game_manager)
{
   	printf("pressed: %d\n", keycode);
	if (keycode == 13) // up
	{
		printf("[%d][%d]\n", game_manager->player_y, game_manager->player_x);
		(game_manager->player_y)++;
		printf("[%d][%d]\n", game_manager->player_y, game_manager->player_x);

		printf("reached %d \n", (game_manager->tile_height));
	}
	else if (keycode == 0) // left
	{
		int x = 200;
		int y = 200;

		while (y < 300)
		{
			while (x < 300)
			{
				my_mlx_pixel_put(game_manager->img, x, y, 0x11FF1111);
				x++;
			}
			x = 0;
			y++;
		}
	}
	else if (keycode == 1) // down
	{

	}
	else if (keycode == 2) // right
	{

	}
	return (0);
}

void	update_game(t_file_data *file_data)
{
	t_game_manager game_manager;

	game_manager = setup_game_manager(file_data);

	t_vars	vars;

	void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, (file_data->resolution)[0][0], (file_data->resolution)[0][1], "Hello world!");
    img.img = mlx_new_image(mlx, (file_data->resolution)[0][0], (file_data->resolution)[0][1]);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	game_manager.mlx = mlx;
	game_manager.win = mlx_win;
	game_manager.img = &img;
	// vars.win = mlx_win;
	// vars.mlx = mlx;

	draw_map(&game_manager, img);

	mlx_hook(mlx_win, 2, 1L<<0, player_input, &game_manager);
    // my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);


    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    mlx_loop(mlx);
}
