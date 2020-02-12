/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:01:59 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/12 14:46:59 by mvan-gin      ########   odam.nl         */
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

static float calculate_ray_distance(t_game_manager *game_manager, t_ray_info *ray_info)
{
    int side;
    int map_y_position;
    int map_x_position;
    int step_x;
    int step_y;

    map_x_position = game_manager->player_tile->x;
    map_y_position = game_manager->player_tile->y;
    calculate_steps(ray_info, &step_x, &step_y);
    while (1)
    {
        if (ray_info->side_dist_x < ray_info->side_dist_y)
        {
            side = 0;
            map_x_position += step_x;
            if (game_manager->map[map_y_position][map_x_position].value == 1)
                break ;
            ray_info->side_dist_x += ray_info->delta_dist_x;
        }
        else
        {
            side = 1;
            map_y_position += step_y;
            if (game_manager->map[map_y_position][map_x_position].value == 1)
                break ;
            ray_info->side_dist_y += ray_info->delta_dist_y;
        }
    }

    float perp_wall_dist;

    if (side == 0)
    {
        perp_wall_dist = fabs((map_x_position - game_manager->player_tile->x + (1 - step_x) / 2) / ray_info->ray_x_dir);
        //printf("x: %f\n", perp_wall_dist);
        return (ray_info->side_dist_x);
    }
    else
    {
        perp_wall_dist = fabs((map_y_position - game_manager->player_tile->y + (1 - step_y) / 2) / ray_info->ray_y_dir);
        //printf("y: %f\n", perp_wall_dist);
        return (ray_info->side_dist_y);
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
    // length = calculate_ray_distance
    ray_distance = calculate_ray_distance(game_manager, &ray_info);

    return (ray_distance);
    // length wordt naar een draw functie gestuurd om de hoogte te berekenen
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

static void draw_wall_line(t_game_manager *game_manager, int res_i, float ray_distance)
{
    int res_height;

    // float percentage;
    int incre;
    int middle;
    

    res_height = (int)(game_manager->file_data->resolution[0][1]);
    // percentage = 1 / ray_distance;
    incre = (((1 / ray_distance) * res_height) * 10);

    // printf("incre:%d\n", incre);


    middle = (res_height / 2) + (incre / 2);

    printf("ray:%f m:%d in:%d\n", ray_distance, middle, incre);

    // my_mlx_pixel_put(game_manager->img_data2, res_i, middle, 0xFF0000);

    while (incre > 0)
    {
        if (middle < 0 || middle > res_height)
            break;
        my_mlx_pixel_put(game_manager->img_data2, res_i, middle, 0xFF0000);
        middle--;
        incre--;
    }
}

static void shoot_rays(t_game_manager *game_manager, float player_dir, int color)
{
    // float   current_ray;
    float   left_ray;
    float   right_ray;
    float   increment;
    int     i;


    i = 0;
    left_ray = player_dir - ((M_PI / 3) / 2);
    right_ray = player_dir + ((M_PI / 3) / 2);
    increment = (right_ray - left_ray) / (game_manager->file_data->resolution[0][0]);

    while (left_ray < right_ray)
    {
        clean_wall_line(game_manager, i);
        draw_wall_line(game_manager, i, calculate_ray(game_manager, left_ray));
        draw_vision_line(game_manager, left_ray, color);
        left_ray += increment;
        i++;
    }
    // draw_wall_line(game_manager, i, calculate_ray(game_manager, game_manager->player_dir));
    // draw_vision_line(game_manager, game_manager->player_dir, color);
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
        printf("%f ", new_x_value);
        printf("%f\n", new_y_value);
        draw_vision_line(game_manager, game_manager->player_dir, 0xFF0000);
        game_manager->player_x = new_x_value;
        game_manager->player_y = new_y_value;
        draw_vision_line(game_manager, game_manager->player_dir, 0x000000);
        shoot_rays(game_manager, game_manager->player_dir, 0x000000);
    }
}
