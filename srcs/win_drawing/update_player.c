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

void            draw_player(t_game_manager *game_manager)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < 10)
	{
		while (x < 10)
		{
			my_mlx_pixel_put(game_manager->img_data, game_manager->player_x + x, game_manager->player_y + y, 0x000000);	
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(game_manager->img_data->mlx, game_manager->img_data->mlx_win, game_manager->img_data->img, 0, 0);
}

int             check_if_availabe(t_game_manager *game_manager, t_game_tile *new_tile)
{
    if (new_tile->value == 0)
    {
        game_manager->player_tile = new_tile;
        printf("next tile available");
        return (1);
    }
    else
    {
        printf("next tile not available");
        return (0);
    }
}

int             change_player_location(t_game_manager *game_manager, int new_x, int new_y)
{
    if (new_y < game_manager->player_tile->start_y) /* Change to tile left */
    {
        if (!check_if_availabe(game_manager, &(game_manager->map)[game_manager->player_tile->y - 1][game_manager->player_tile->x]))
        {
            printf("Something is in the way");
            return (0);
        }

    }

    game_manager->player_x = new_x;
    game_manager->player_y = new_y;
    printf("newvalue: [%d][%d]\n", game_manager->player_x, game_manager->player_y);
    

    draw_player(game_manager);
    return (0);
}

void            update_player(t_game_manager *game_manager, int x_diff, int y_diff)
{
    int new_x;
    int new_y;
    /*
        Check tile that it's supposed to go to has a value of one
    */

    printf("oldvalue: [%d][%d]\n", game_manager->player_x, game_manager->player_y);

    new_x = game_manager->player_x + x_diff;
    new_y = game_manager->player_y + y_diff;

    change_player_location(game_manager, new_x, new_y);
}