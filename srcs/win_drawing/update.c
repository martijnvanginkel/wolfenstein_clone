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

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

static int		widest_map_line(t_map_tile **map, int map_height)
{
	int x;
	int y;
	int widest;

	x = 0;
	y = 0;
	widest = 0;
	while (y < map_height)
	{
		while (map[y][x].value != -1)
			x++;
		if (x > widest)
			widest = x;
		x = 0;
		y++;
	}
	return (widest);
}

static void		draw_map(t_file_data *file_data)
{
	int x = 0;
	int y = 0;

	int tile_width;
	int	tile_height;

	tile_width = (file_data->resolution)[0][0] / file_data->map_width;
	tile_height = (file_data->resolution)[0][1] / file_data->map_height;
	printf("tile_width : %d\n", tile_width);
	printf("tile_height: %d\n", tile_height);

	printf("value:%d\n", (file_data->map)[1][1].value);

	while (y < file_data->map_height)
	{
		while (file_data->map[y][x].value != -1)
		{
			printf("%d ", file_data->map[y][x].value);
			x++;
		}
		while (x < file_data->map_width)
		{
			printf("%d ", 0);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}



}

void	update_game(t_file_data *file_data)
{
	printf("\no--------------------o\n");
	
	file_data->map_width = widest_map_line(file_data->map, file_data->map_height);

	/* Heb de width en height van de map nu */

	draw_map(file_data);


	//printf("%d", *(file_data->resolution)[0]);
}
