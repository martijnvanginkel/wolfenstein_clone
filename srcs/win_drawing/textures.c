/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 16:01:06 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/26 09:29:56 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

void            my_image_put(t_data *img_data, t_coordinates cords, t_data *img_data2, t_coordinates cords2)
{
    char    *dst;
	char	*dst2;

    dst = img_data->addr + ((int)cords.y * img_data->line_length + (int)cords.x * (img_data->bits_per_pixel / 8));
	dst2 = img_data2->addr + ((int)cords2.y * img_data2->line_length + (int)cords2.x * (img_data2->bits_per_pixel / 8));

	*(unsigned int *)dst2 = *(unsigned int *)dst;
}

static t_data	*get_texture(t_game_manager *gm, char *path)
{
	t_data  *img;
	int		img_width;
	int		img_height;

	img = (t_data *)malloc(sizeof(t_data) * 1);
	if (!img)
		return (0);
	img->mlx = mlx_init();
    img->img = mlx_png_file_to_image(img->mlx, path, &img_width, &img_height);
	if (img->img == 0)
		return (0);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->mlx_win = gm->world_image->mlx_win;
	img->width = img_width;
	img->height = img_height;
	return (img);
}

void	get_textures(t_game_manager *gm)
{
	t_texture_images *textures;

	textures = (t_texture_images *)malloc(sizeof(t_texture_images) * 1);
	if (!textures)
		return ;
	textures->north_tex = get_texture(gm, *(gm->file_data->north_texture));
	textures->east_tex = get_texture(gm, *(gm->file_data->east_texture));
	textures->south_tex = get_texture(gm, *(gm->file_data->south_texture));
	textures->west_tex = get_texture(gm, *(gm->file_data->west_texture));
	gm->textures = textures;
}