/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shoot_3d_rays.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 09:51:19 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/14 10:11:57 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static int  increase_ray_distance(t_game_tile tile, t_ray_info *ray, int side)
{
    if (tile.value == 1)
    {
        if (side == 0)
            ray->final_dist = ray->side_dist_x;
        else 
            ray->final_dist = ray->side_dist_y;
        return (0);
    }
    if (side == 0)
        ray->side_dist_x += ray->delta_dist_x;
    else
        ray->side_dist_y += ray->delta_dist_y;
    return (1);
}

static float calculate_ray_distance(t_game_manager *gm, t_ray_info *ray_info)
{
    int side;
    int map_y;
    int map_x;
    int step_x;
    int step_y;

    map_x = gm->player_tile->x;
    map_y = gm->player_tile->y;
    calculate_steps(ray_info, &step_x, &step_y);
    while (1)
    {
        if (ray_info->side_dist_x < ray_info->side_dist_y)
        {
            side = 0;
            map_x += step_x;
        }
        else
        {
            side = 1;
            map_y += step_y;
        }
        if (!increase_ray_distance(gm->map[map_y][map_x], ray_info, side))
            return (ray_info->final_dist);
    }
}


static float calculate_ray(t_game_manager *game_manager, float ray_dir)
{
    t_ray_info  ray_info;
    float       ray_distance;

    ray_info.ray_dir = ray_dir;
    ray_info.ray_x_dir = sin(ray_dir);
    ray_info.ray_y_dir = cos(ray_dir);

    calculate_side_distances(game_manager, &ray_info);
    calculate_deltas(game_manager, &ray_info);
    ray_distance = calculate_ray_distance(game_manager, &ray_info);
    ray_info.perp_dist = cos(game_manager->player_dir - ray_dir) * ray_distance;
    return (ray_info.perp_dist);
}

/* Container function for shooting all the rays in the player's view */
void shoot_rays(t_game_manager *game_manager, float player_dir, int color)
{
    float   ray;
    int     cur_px;
    float start_incr;
    float start;
    float player_length;

    start = 1;
    start_incr = 2.0 / (float)(game_manager->file_data->resolution[0][0]);
    player_length = fabs(start) / tan(M_PI / 6);
    cur_px = game_manager->file_data->resolution[0][0];
    while (start > -1)
    {
        ray = game_manager->player_dir + atan(start / player_length);
        start -= start_incr;  
        cur_px--;    
        draw_2d_vision_line(game_manager, ray, color);
        clean_3d_wall_line(game_manager, cur_px);
        draw_3d_wall_line(game_manager, cur_px, calculate_ray(game_manager, ray));
    }
    mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
    mlx_put_image_to_window(game_manager->img_data2->mlx, game_manager->img_data2->mlx_win, game_manager->img_data2->img, 0, 0);
}