/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_and_ceiling.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/19 15:56:00 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/20 12:03:29 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void    draw_floor(t_game_manager *game_manager)
{
    int x;
    int y;
    int res_width;
    int res_height;
    int color_code;

    color_code = dec_from_hex_color(game_manager->file_data->floor_color[0]);
    res_width = game_manager->file_data->resolution[0][0];
    res_height = game_manager->file_data->resolution[0][1];
    y = res_height / 2;
    while (y < res_height)
    {
        while (x < res_width)
        {
            my_mlx_pixel_put2(game_manager, x, y, color_code);
            x++;
        }
        x = 0;
        y++;
    }
    mlx_put_image_to_window(game_manager->world_image->mlx, game_manager->world_image->mlx_win, game_manager->world_image->img, 0, 0);
}

static void    draw_ceiling(t_game_manager *game_manager)
{
    int x;
    int y;
    int res_width;
    int res_height;
    int color_code;

    color_code = dec_from_hex_color(game_manager->file_data->ceiling_color[0]);
    res_width = game_manager->file_data->resolution[0][0];
    res_height = game_manager->file_data->resolution[0][1];
    y = 0;
    while (y < res_height / 2)
    {
        while (x < res_width)
        {
            my_mlx_pixel_put2(game_manager, x, y, color_code);
            x++;
        }
        x = 0;
        y++;
    }
    mlx_put_image_to_window(game_manager->world_image->mlx, game_manager->world_image->mlx_win, game_manager->world_image->img, 0, 0);
}

void    draw_floor_and_ceiling(t_game_manager *game_manager)
{
    draw_ceiling(game_manager);
    draw_floor(game_manager);
}