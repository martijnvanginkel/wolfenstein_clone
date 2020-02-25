/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shoot_3d_rays.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 09:51:19 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/25 12:43:56 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void set_final_ray_info(t_ray_info *ray, int side)
{
    if (side == 0)
    {
        if (ray->ray_x_dir < 0)
            ray->side_hit = 3;
        else
            ray->side_hit = 1;
        ray->final_dist = ray->side_dist_x;
    }
    else
    {
        if (ray->ray_y_dir < 0)
            ray->side_hit = 2;
        else
            ray->side_hit = 0;
        ray->final_dist = ray->side_dist_y;
    } 
}

static int  increase_ray_distance(t_game_tile tile, t_ray_info *ray, int side)
{
    if (tile.value == 1)
    {
        set_final_ray_info(ray, side);
        ray->tile_hit = &tile;
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

static  float   get_texture_start_percentage(t_game_manager *gm, t_ray_info *ray)
{
    int x_cord;
    int y_cord;
    int from_left_side;
    float perc;

    x_cord = (int)gm->player_x + (int)(ray->eucl_dist * ray->ray_x_dir);
    y_cord = (int)gm->player_y + (int)(ray->eucl_dist * ray->ray_y_dir);
    from_left_side = x_cord % gm->tile_width;
    perc = (float)1 / (float)gm->tile_width;
    perc = perc * (float)from_left_side;
    return (perc);
}

static void     find_texture_line(t_game_manager *gm, t_ray_info *ray, int world_x_cord)
{
    float perc;

    perc = get_texture_start_percentage(gm, ray);


    int x = (int)((float)gm->textures->south_tex->width * perc);
    printf("x:%d\n", x);
    float y = 0;
    float y_incr;

    int res_height;
    int line_height;
    int middle;

    res_height = (int)(gm->file_data->resolution[0][1]);
    line_height = (((1 / ray->perp_dist) * res_height) * 25);
    middle = (res_height / 2) + (line_height / 2);
    
    y_incr = (float)gm->textures->south_tex->height / (float)line_height;
    
    // printf("y_incr:%f\n", y_incr);

    while (line_height > 0)
    {
        //my_mlx_pixel_put2(gm, x, middle, 0x000000);  
        my_image_put(gm->textures->south_tex, x, y, world_x_cord, middle, gm->world_image);
        y += y_incr;

        //printf("[%f] ", y);
        middle--;
        line_height--;
    }




}

static t_ray_info calculate_ray(t_game_manager *gm, float ray_dir)
{
    t_ray_info  ray;

    ray.ray_dir = ray_dir;
    ray.ray_x_dir = sin(ray_dir);
    ray.ray_y_dir = cos(ray_dir);
    calculate_side_distances(gm, &ray);
    calculate_deltas(gm, &ray);
    ray.eucl_dist = calculate_ray_distance(gm, &ray);
    ray.perp_dist = cos(gm->player_dir - ray_dir) * ray.eucl_dist;
    return (ray);
}

static void draw_wall_line(t_game_manager *gm , int cur_x, float ray_dir)
{
    t_ray_info ray;

    ray = calculate_ray(gm, ray_dir);
    find_texture_line(gm, &ray, cur_x);
}

/* Container function for shooting all the rays in the player's view */
void shoot_rays(t_game_manager *gm, float player_dir, int color)
{
    float   ray_dir;
    int     cur_px;
    float   start_incr;
    float   start;
    float   player_length;

    start = 1;
    start_incr = 2.0 / (float)(gm->file_data->resolution[0][0]);
    player_length = fabs(start) / tan(M_PI / 6);
    cur_px = gm->file_data->resolution[0][0];
    while (start > -1)
    {
        ray_dir = gm->player_dir + atan(start / player_length);
        start -= start_incr;  
        cur_px--;    
        draw_2d_vision_line(gm, ray_dir, color);
        draw_wall_line(gm, cur_px, ray_dir);
    }
    mlx_put_image_to_window(gm->map_image->mlx, gm->map_image->mlx_win, gm->map_image->img, 0, 0);
    mlx_put_image_to_window(gm->world_image->mlx, gm->world_image->mlx_win, gm->world_image->img, 0, 0);
}