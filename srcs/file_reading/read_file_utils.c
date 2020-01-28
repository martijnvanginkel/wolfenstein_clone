/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_file_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 17:44:11 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/28 17:48:07 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_file_data     empty_file_data(void)
{
    t_file_data file_data;

    file_data.full_file = 0;
    file_data.resolution = 0;
    file_data.north_texture = 0;
    file_data.south_texture = 0;
    file_data.west_texture = 0;
    file_data.east_texture = 0;
    file_data.sprite_texture = 0;
    file_data.floor_color = 0;
    file_data.ceiling_color = 0;
    file_data.map = 0;
    return (file_data);
}

int            all_info_filled(t_file_data *data)
{
    if (data->resolution != 0 &&
        data->north_texture != 0 &&
        data->south_texture != 0 &&
        data->west_texture != 0 &&
        data->east_texture &&
        data->sprite_texture != 0 &&
        data->floor_color != 0 &&
        data->ceiling_color != 0)
        return (1);
    return (0);
}

void		print_file_data(t_file_data *file_data)
{
	printf("width : %d \n", (file_data->resolution)[0][0]);
	printf("height : %d \n", (file_data->resolution)[0][1]);
	printf("n_tex : %s \n", *(file_data->north_texture));
	printf("n_tex : %s \n", *(file_data->south_texture));
	printf("n_tex : %s \n", *(file_data->west_texture));
    printf("n_tex : %s \n", *(file_data->east_texture));
    printf("n_tex : %s \n", *(file_data->sprite_texture));
    printf("floor: %d\n %d\n %d\n", (file_data->floor_color)[0][0], (file_data->floor_color)[0][1], (file_data->floor_color)[0][2]);
    printf("ceiling: %d\n %d\n %d\n", (file_data->ceiling_color)[0][0], (file_data->ceiling_color)[0][1], (file_data->ceiling_color)[0][2]);
}

