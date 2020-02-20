/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quit_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/20 15:52:43 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/20 15:59:27 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../minilibx/mlx.h"
#include "../../cub3d.h"

static void     free_textures(t_game_manager *gm)
{
    free(gm->textures->north_tex);
    free(gm->textures->east_tex);
    free(gm->textures->south_tex);
    free(gm->textures->west_tex);
    free(gm->textures);
}

void			quit_game(t_game_manager *gm)
{
    free_textures(gm);
    write(1, "Bye!", 4);
}