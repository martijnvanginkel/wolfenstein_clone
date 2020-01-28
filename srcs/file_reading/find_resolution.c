/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_resolution.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 16:58:55 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/28 17:16:15 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static void	str_to_digit(int *answer, char *str, int *index)
{
	while (str[*index] >= '0' && str[*index] <= '9')
	{
		*answer = *answer * 10 + (str[*index] - 48);
		(*index)++;
	}
}

static int	*initialize_resolution(void)
{
	int	*resolution;

	resolution = (int *)malloc(sizeof(int) * 2);
	if (!resolution)
		return (0);
	resolution[0] = 0;
	resolution[1] = 0;
	return (resolution);
}

static int	resolution_found(int *resolution)
{
	if (resolution[0] != 0 && resolution[1] != 0)
		return (1);
	else
		return (0);
}

int			find_resolution(char *file_string, int *index, t_file_data *data,
							t_id_tuple *id_tuple)
{
	int *resolution;

	resolution = initialize_resolution();
	if (!resolution)
		return (0);
	loop_empty_space(file_string, index);
	str_to_digit(&resolution[0], file_string, index);
	loop_empty_space(file_string, index);
	str_to_digit(&resolution[1], file_string, index);
	if (resolution_found(resolution) && is_empty_line(file_string, *index))
	{
		*(id_tuple->value) = resolution;
		return (1);
	}
	return (0);
}
