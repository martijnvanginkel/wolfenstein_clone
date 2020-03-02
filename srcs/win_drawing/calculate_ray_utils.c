/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_ray_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 10:02:51 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/28 15:31:33 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

void calculate_side_distances(t_game_manager *game_manager, t_ray_info *ray_info)
{
    float x;
    float y;

    if (ray_info->ray_x_dir > 0)
        x = 1 - (game_manager->player_x - (int)game_manager->player_x);
    else if (ray_info->ray_x_dir < 0)
        x = (game_manager->player_x - (int)game_manager->player_x);
    if (ray_info->ray_y_dir < 0)
        y = game_manager->player_y - (int)game_manager->player_y;
    else if (ray_info->ray_y_dir > 0)
        y = 1 - (game_manager->player_y - (int)game_manager->player_y);
    ray_info->side_dist_x = fabs(x / sin(ray_info->ray_dir));
    ray_info->side_dist_y = fabs(y / cos(ray_info->ray_dir));
}

void calculate_deltas(t_game_manager *game_manager, t_ray_info *ray_info)
{
    ray_info->delta_dist_x = fabs(1 / ray_info->ray_x_dir);
    ray_info->delta_dist_y = fabs(1 / ray_info->ray_y_dir);
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