/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 09:55:51 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/14 10:07:59 by mvan-gin      ########   odam.nl         */
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

void draw_2d_vision_line(t_game_manager *game_manager, double dir, int color)
{
    int res_width;
    int res_height;
    double x = game_manager->player_x;
    double y = game_manager->player_y;

    res_width = game_manager->file_data->resolution[0][0];
    res_height = game_manager->file_data->resolution[0][1];
    while (x > 0 && x < res_width && y > 0 && y < res_height)
    {
        if (!available_pixel(game_manager, (int)x, (int)y))
        {
            break;
        }
        my_mlx_pixel_put(game_manager->img_data, x, y, color);
        x += sin(dir);
        y += cos(dir);
    }
}

void clean_3d_wall_line(t_game_manager *game_manager, int x_value)
{
    int height;
    int y;

    y = 0;
    height = game_manager->file_data->resolution[0][1];
    while (y < height)
    {
        my_mlx_pixel_put(game_manager->img_data2, x_value, y, 0x000000);
        y++;
    }
}

void draw_3d_wall_line(t_game_manager *game_manager, int res_i, float perp_distance)
{
    int res_height;
    int incre;
    int middle;

    res_height = (int)(game_manager->file_data->resolution[0][1]);
    incre = (((1 / perp_distance) * res_height) * 10);
    middle = (res_height / 2) + (incre / 2);
    while (incre > 0)
    {
        if (middle < 0 || middle > res_height)
            break;
        my_mlx_pixel_put(game_manager->img_data2, res_i, middle, 0xFF0000);
        middle--;
        incre--;
    }
}