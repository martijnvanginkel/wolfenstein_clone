/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_color.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 17:27:35 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/28 17:42:33 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int		valid_rgb_number(int number)
{
	if (number >= 0 && number <= 255)
		return (1);
	else
		return (0);
}

static int		loop_and_find_color(int *color, char *file_string, int *index)
{
	loop_empty_space(file_string, index);
	if (!valid_rgb_number(str_to_number(color, file_string, index)))
		return (0);
	loop_empty_space(file_string, index);
	return (1);
}

int				find_color(char *file_string, int *index,
				t_file_data *file_data, t_id_tuple *id_tuple)
{
	int *rgb_colors;

	rgb_colors = (int *)malloc(sizeof(int) * 3);
	if (!rgb_colors)
		return (0);
	if (!loop_and_find_color(&rgb_colors[0], file_string, index))
		return (0);
	if (file_string[(*index)++] != ',')
	{
		free(rgb_colors);
		return (0);
	}
	if (!loop_and_find_color(&rgb_colors[1], file_string, index))
		return (0);
	if (file_string[(*index)++] != ',')
	{
		free(rgb_colors);
		return (0);
	}
	if (!loop_and_find_color(&rgb_colors[2], file_string, index))
		return (0);
	*(id_tuple->value) = rgb_colors;
	return (1);
}
