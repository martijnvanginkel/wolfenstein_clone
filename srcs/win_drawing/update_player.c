/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:01:59 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/10 17:38:54 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static int          available_pixel(t_game_manager *g_m, int x, int y)
{
    if (g_m->map[y / g_m->tile_height][x / g_m->tile_width].value != 1)
    {
        return (1);
    }
    return (0);
}        

static void         draw_vision_line(t_game_manager *game_manager, double dir, int color)
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

static void            find_x_point(t_game_manager *game_manager)
{

    int     wall_hit = 0;

    double  side_dist_x;
    double  side_dist_y;

    double  delta_dist_x;
    double  delta_dist_y;

    // int     step_x;
    // int     step_y;

    // delta_dist_x = fabs(1 / game_manager->x_dir);
    // delta_dist_y = fabs(1 / game_manager->y_dir);

    // int hit = 0;

    double x = game_manager->player_x;
    double y = game_manager->player_y;

    if (game_manager->x_dir > 0)
    {
        while (x < (game_manager->player_tile->start_x + game_manager->tile_width))
            x++;
    }
    else if (game_manager->x_dir < 0)
    {
        while (x > game_manager->player_tile->start_x)
            x--;
    }
    if (game_manager->y_dir < 0)
    {
        while (y > game_manager->player_tile->start_y)
        {
            printf("1");
            y--;
        }
    }
    else if (game_manager->y_dir > 0)
    {
        while (y < game_manager->player_tile->start_y + game_manager->tile_height)
        {
            printf("2");
            y++;
        }
    }
    side_dist_x = (game_manager->player_x - x) / sin(game_manager->player_dir);
    side_dist_y = (game_manager->player_y - y) / cos(game_manager->player_dir);

    printf("\nx_dist:%f\n", side_dist_x);
    printf("y_dist:%f\n", side_dist_y);



    delta_dist_x = fabs(game_manager->tile_width / game_manager->x_dir);
    delta_dist_y = fabs(game_manager->tile_height / game_manager->y_dir);
    printf("\ndelta_dist_x: %f \n", delta_dist_x);
    printf("\ndelta_dist_y: %f \n", delta_dist_y);

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

    while (wall_hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x_position += step_x;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y_position += step_y;
        }

        if (game_manager->map[map_y_position][map_x_position].value == 1)
        {
            printf("values:\n[%d][%d]\n", game_manager->map[map_y_position][map_x_position].x, game_manager->map[map_y_position][map_x_position].y);
            wall_hit = 1;
        }
    }
    
    
    
    //printf("\n\nmycalc%f\n\n", (game_manager->player_x - x) / sin(game_manager->player_dir));


    //my_mlx_pixel_put(game_manager->img_data, x, game_manager->player_y, 0x000000);


}

static void            calculate_delta(t_game_manager *game_manager)
{
    double player_x;
    double player_y;

    player_x = game_manager->player_x;
    player_y = game_manager->player_y;

    printf("player_pos: [%f][%f]\n", player_x, player_y);
    printf("x_dir: %f", game_manager->x_dir);
    printf("y_dir: %f", game_manager->y_dir);

    find_x_point(game_manager);
}

void            rotate_player(t_game_manager *game_manager, double rotation)
{
    draw_vision_line(game_manager, game_manager->player_dir, 0xFF0000);
    game_manager->player_dir = (game_manager->player_dir + rotation);
    game_manager->x_dir = sin(game_manager->player_dir);
	game_manager->y_dir = cos(game_manager->player_dir);

    printf("\nx_dir:[%f] | y_dir[%f]\n", game_manager->x_dir, game_manager->y_dir);

    draw_vision_line(game_manager, game_manager->player_dir, 0x000000);

    calculate_delta(game_manager);

}

void            move_player(t_game_manager *game_manager, double walk_speed)
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

