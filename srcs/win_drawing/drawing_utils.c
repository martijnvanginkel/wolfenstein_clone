/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   drawing_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 09:55:51 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/25 09:54:41 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

void            my_mlx_pixel_put(t_game_manager *gm, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || y < 0 || x > gm->file_data->resolution[0][0] - 1 || y > gm->file_data->resolution[0][1] - 1)
        return ;
    dst = gm->map_image->addr + (y * gm->map_image->line_length + x * (gm->map_image->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            my_mlx_pixel_put2(t_game_manager *gm, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || y < 0 || x > gm->file_data->resolution[0][0] - 1 || y > gm->file_data->resolution[0][1] - 1)
        return ;
    dst = gm->world_image->addr + (y * gm->world_image->line_length + x * (gm->world_image->bits_per_pixel / 8));
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
        my_mlx_pixel_put(game_manager, x, y, color);
        x += sin(dir);
        y += cos(dir);
    }
}

void draw_3d_wall_line(t_game_manager *game_manager, int res_i, t_ray_info ray)
{
    int res_height;
    int incre;
    int middle;

    return ;
    /* 
        Ray is hier binnen. De eucl_dist moet nog in de ray opgeslagen worden
        
    
    */



    res_height = (int)(game_manager->file_data->resolution[0][1]);
    incre = (((1 / ray.perp_dist) * res_height) * 10);
    middle = (res_height / 2) + (incre / 2);
    while (incre > 0)
    {
        /* temp test for different side-colors */
        if (ray.side_hit == 0)
        {

            my_mlx_pixel_put2(game_manager, res_i, middle, 0xFF0000);
        }
        else
        {
            my_mlx_pixel_put2(game_manager, res_i, middle, 0x000000);
        }
        
        middle--;
        incre--;
    }
}
