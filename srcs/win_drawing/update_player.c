/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:01:59 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/11 16:01:01 by mvan-gin      ########   odam.nl         */
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

    mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
}

static float calculate_side_distances(t_game_manager *game_manager, float *side_dist_x, float *side_dist_y)
{
    float x;
    float y;

    x = game_manager->player_x;
    y = game_manager->player_y;
    if (game_manager->x_dir > 0)
        x = (game_manager->player_tile->start_x + game_manager->tile_width);
    else if (game_manager->x_dir < 0)
        x = game_manager->player_tile->start_x;
    if (game_manager->y_dir < 0)
        y = game_manager->player_tile->start_y;
    else if (game_manager->y_dir > 0)
        y = game_manager->player_tile->start_y + game_manager->tile_height;
    *side_dist_x = fabs((game_manager->player_x - x) / sin(game_manager->player_dir));
    *side_dist_y = fabs((game_manager->player_y - y) / cos(game_manager->player_dir));
}

static void calculate_ray_distance(t_game_manager *game_manager)
{
    int side;

    float side_dist_x;
    float side_dist_y;

    float delta_dist_x;
    float delta_dist_y;


    calculate_side_distances(game_manager, &side_dist_x, &side_dist_y);
    
    delta_dist_x = fabs(game_manager->tile_width / game_manager->x_dir);
    delta_dist_y = fabs(game_manager->tile_height / game_manager->y_dir);

    int map_y_position;
    int map_x_position;
    int step_x;
    int step_y;

    map_x_position = game_manager->player_tile->x;
    map_y_position = game_manager->player_tile->y;

    if (game_manager->x_dir < 0)
    {
        step_x = -1;
    }
    else
    {
        step_x = 1;
    }
    if (game_manager->y_dir < 0)
    {
        step_y = -1;
    }
    else
    {
        step_y = 1;
    }

    while (1)
    {
        if (side_dist_x < side_dist_y)
        {
            side = 0;
            map_x_position += step_x;
            if (game_manager->map[map_y_position][map_x_position].value == 1)
                break ;
            side_dist_x += delta_dist_x;
        }
        else
        {
            side = 1;
            map_y_position += step_y;
            if (game_manager->map[map_y_position][map_x_position].value == 1)
                break ;
            side_dist_y += delta_dist_y;
        }
        // if (game_manager->map[map_y_position][map_x_position].value == 1)
        // {
        //     printf("values:\n[%d][%d]\n", game_manager->map[map_y_position][map_x_position].x, game_manager->map[map_y_position][map_x_position].y);
        //     //printf("side_dist: %f %f\n", side_dist_x, side_dist_y);
        //     // my_mlx_pixel_put(game_manager->img_data, game_manager->map[map_y_position][map_x_position].start_x, game_manager->map[map_y_position][map_x_position].start_y, 0x000000);
        //     wall_hit = 1;
        // }
    }



    //printf("\nside_x: %f %f\n", side_dist_x, side_dist_y);
    //mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
    if (side == 0)
    {
        printf("$x%f\n", side_dist_x);
        //perpWallDist = fabs((map_x_position - game_manager->player_x + (1 - step_x) / 2) / game_manager->x_dir);
    }
    else
    {
        printf("$y%f\n", side_dist_y);
        //perpWallDist = fabs((map_y_position - game_manager->player_y + (1 - step_y) / 2) / game_manager->y_dir);
    }
    
}

void rotate_player(t_game_manager *game_manager, double rotation)
{
    draw_vision_line(game_manager, game_manager->player_dir, 0xFF0000);
    game_manager->player_dir = (game_manager->player_dir + rotation);
    game_manager->x_dir = sin(game_manager->player_dir);
    game_manager->y_dir = cos(game_manager->player_dir);

    // printf("\nx_dir:[%f] | y_dir[%f]\n", game_manager->x_dir, game_manager->y_dir);

    draw_vision_line(game_manager, game_manager->player_dir, 0x000000);

    calculate_ray_distance(game_manager);
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
    }
}
