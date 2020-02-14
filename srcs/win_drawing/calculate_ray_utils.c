/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_ray_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 10:02:51 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/14 10:09:55 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

void calculate_side_distances(t_game_manager *game_manager, t_ray_info *ray_info)
{
    float x;
    float y;

    x = game_manager->player_x;
    y = game_manager->player_y;
    if (ray_info->ray_x_dir > 0)
        x = (game_manager->player_tile->start_x + game_manager->tile_width);
    else if (ray_info->ray_x_dir < 0)
        x = game_manager->player_tile->start_x;
    if (ray_info->ray_y_dir < 0)
        y = game_manager->player_tile->start_y;
    else if (ray_info->ray_y_dir > 0)
        y = game_manager->player_tile->start_y + game_manager->tile_height;
    ray_info->side_dist_x = fabs((game_manager->player_x - x) / sin(ray_info->ray_dir));
    ray_info->side_dist_y = fabs((game_manager->player_y - y) / cos(ray_info->ray_dir));
}

void calculate_deltas(t_game_manager *game_manager, t_ray_info *ray_info)
{
    ray_info->delta_dist_x = fabs(game_manager->tile_width / ray_info->ray_x_dir);
    ray_info->delta_dist_y = fabs(game_manager->tile_height / ray_info->ray_y_dir);
}

void calculate_steps(t_ray_info *ray_info, int *step_x, int *step_y)
{
    if (ray_info->ray_x_dir < 0)
        *step_x = -1;
    else
        *step_x = 1;
    if (ray_info->ray_y_dir < 0)
        *step_y = -1;
    else
        *step_y = 1;
}