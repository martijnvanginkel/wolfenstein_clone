/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:01:59 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/05 15:46:02 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void            draw_vision_line(t_game_manager *game_manager, int color)
{
    int res_width;
    int res_height;
    double x = game_manager->player_x;
    double y = game_manager->player_y;

    res_width = game_manager->file_data->resolution[0][0];
    res_height = game_manager->file_data->resolution[0][1];
    while (x > 0 && x < res_width && y > 0 && y < res_height)
    {
        if (game_manager->map[(int)y / game_manager->tile_height][(int)x / game_manager->tile_width].value == 1)
        {
            break;
        }
        my_mlx_pixel_put(game_manager->img_data, x, y, color);
        x += sin(game_manager->player_dir);
        y += cos(game_manager->player_dir);
    }  
    mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
}

void            rotate_player(t_game_manager *game_manager, double rotation)
{
    draw_vision_line(game_manager, 0xFF0000);
    game_manager->player_dir = (game_manager->player_dir + rotation);
    draw_vision_line(game_manager, 0x000000);
}

void            move_player(t_game_manager *game_manager)

