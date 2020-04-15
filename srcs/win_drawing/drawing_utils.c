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

void            my_mlx_pixel_put(t_game_manager *gm, int x, int y, int color)
{
    // char    *dst;

    // if (x < 0 || y < 0 || x > gm->file_data->resolution[0][0] - 1 || y > gm->file_data->resolution[0][1] - 1)
    //     return ;
    // dst = gm->map_image->addr + (y * gm->map_image->line_length + x * (gm->map_image->bits_per_pixel / 8));
    // *(unsigned int*)dst = color;
}

void            my_mlx_pixel_put2(t_game_manager *gm, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || y < 0 || x > gm->file_data->resolution[0][0] - 1 || y > gm->file_data->resolution[0][1] - 1)
        return ;
    dst = gm->world_image->addr + (y * gm->world_image->line_length + x * (gm->world_image->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void draw_2d_vision_line(t_game_manager *gm, double dir, int color)
{
    // int res_width;
    // int res_height;
    // float x = (float)gm->player_x * (float)gm->tile_width;
    // float y = (float)gm->player_y * (float)gm->tile_height;

    // res_width = gm->file_data->resolution[0][0];
    // res_height = gm->file_data->resolution[0][1];
    // int i = 0;

    // // while (x > 0 && x < res_width && y > 0 && y < res_height)
    // while (i < 300)
    // {
    //     // if (!available_pixel(game_manager, (int)x, (int)y))
    //     // {
    //     //     break;
    //     // }
    //     my_mlx_pixel_put(gm, (int)x, (int)y, color);
    //     x += sin(dir);
    //     y += cos(dir);
    //     i++;
    // }
}
