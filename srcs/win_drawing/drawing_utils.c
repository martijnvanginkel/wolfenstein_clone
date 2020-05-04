/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 09:55:51 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/03/03 17:20:17 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

void            my_mlx_pixel_put(t_game_manager *gm, int x, int y, int color) { }

void            my_mlx_pixel_put2(t_game_manager *gm, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || y < 0 || x > gm->file_data->resolution[0][0] - 1 || y > gm->file_data->resolution[0][1] - 1)
        return ;
    dst = gm->world_image->addr + (y * gm->world_image->line_length + x * (gm->world_image->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_2d_vision_line(t_game_manager *gm, double dir, int color) { }
