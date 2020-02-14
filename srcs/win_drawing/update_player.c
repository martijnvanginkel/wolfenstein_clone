/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:01:59 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/14 09:48:21 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static int available_pixel(t_game_manager *g_m, int x, int y)
{
    if (g_m->map[y / g_m->tile_height][x / g_m->tile_width].value != 1)
    {
        return (1);
    }
    return (0);
}

static void draw_vision_line(t_game_manager *game_manager, double dir, int color)
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

static void calculate_side_distances(t_game_manager *game_manager, t_ray_info *ray_info)
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

static void calculate_deltas(t_game_manager *game_manager, t_ray_info *ray_info)
{
    ray_info->delta_dist_x = fabs(game_manager->tile_width / ray_info->ray_x_dir);
    ray_info->delta_dist_y = fabs(game_manager->tile_height / ray_info->ray_y_dir);
}

static void calculate_steps(t_ray_info *ray_info, int *step_x, int *step_y)
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

static void clean_wall_line(t_game_manager *game_manager, int x_value)
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

static void draw_wall_line(t_game_manager *game_manager, int res_i, float perp_distance)
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

static void shoot_rays(t_game_manager *game_manager, float player_dir, int color)
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
        draw_vision_line(game_manager, ray, color);
        clean_wall_line(game_manager, cur_px);
        draw_wall_line(game_manager, cur_px, calculate_ray(game_manager, ray));
    }
    mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
    mlx_put_image_to_window(game_manager->img_data2->mlx, game_manager->img_data2->mlx_win, game_manager->img_data2->img, 0, 0);
}

void rotate_player(t_game_manager *game_manager, double rotation)
{
    shoot_rays(game_manager, game_manager->player_dir, 0xFF0000);
    
    draw_vision_line(game_manager, game_manager->player_dir, 0xFF0000);
    game_manager->player_dir = (game_manager->player_dir + rotation);
    game_manager->x_dir = sin(game_manager->player_dir);
    game_manager->y_dir = cos(game_manager->player_dir);
    draw_vision_line(game_manager, game_manager->player_dir, 0x000000);

    shoot_rays(game_manager, game_manager->player_dir, 0x000000);
}

void move_player(t_game_manager *game_manager, double walk_speed)
{
    double new_x_value;
    double new_y_value;

    new_x_value = game_manager->player_x + (walk_speed * sin(game_manager->player_dir));
    new_y_value = game_manager->player_y + (walk_speed * cos(game_manager->player_dir));
    if (available_pixel(game_manager, new_x_value, new_y_value))
    {
        game_manager->player_tile = &game_manager->map[(int)new_y_value / game_manager->tile_height][(int)new_x_value / game_manager->tile_width];
        draw_vision_line(game_manager, game_manager->player_dir, 0xFF0000);
        game_manager->player_x = new_x_value;
        game_manager->player_y = new_y_value;
        draw_vision_line(game_manager, game_manager->player_dir, 0x000000);
        shoot_rays(game_manager, game_manager->player_dir, 0x000000);
    }
}
