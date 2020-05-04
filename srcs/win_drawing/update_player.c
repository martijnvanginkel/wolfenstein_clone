/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_player.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 15:01:59 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/03/10 11:02:11 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

int available_pixel(t_game_manager *g_m, int x, int y)
{
    if (g_m->map[y][x].value != 1)
    {
        return (1);
    }
    return (0);
}

void rotate_player(t_game_manager *game_manager, double rotation)
{
    game_manager->player_dir = (game_manager->player_dir + rotation);
    game_manager->x_dir = sin(game_manager->player_dir);
    game_manager->y_dir = cos(game_manager->player_dir);å
    draw_floor_and_ceiling(game_manager);
    shoot_rays(game_manager, game_manager->player_dir, 0x000000);
}

void move_player(t_game_manager *game_manager, double walk_speed, double rotation)
{
    double new_x_value;
    double new_y_value;

    new_x_value = game_manager->player_x + (walk_speed * sin(game_manager->player_dir + rotation));
    new_y_value = game_manager->player_y + (walk_speed * cos(game_manager->player_dir + rotation));
    if (available_pixel(game_manager, new_x_value, new_y_value))
    {
        game_manager->player_tile = &game_manager->map[(int)new_y_value][(int)new_x_value];
        game_manager->player_x = new_x_value;
        game_manager->player_y = new_y_value;
        draw_floor_and_ceiling(game_manager);
        shoot_rays(game_manager, game_manager->player_dir, 0x000000);
    }
}
