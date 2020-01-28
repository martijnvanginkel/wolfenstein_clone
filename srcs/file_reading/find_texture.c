/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_texture.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/28 17:16:41 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/28 17:27:16 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	texture_malloc_size(char *file_string, int *index)
{
	int	malloc_size;

	malloc_size = 0;
	while (file_string[*index] != '\0' &&
			file_string[*index] != '\n' &&
			file_string[*index] != ' ' &&
			file_string[*index] != '\t')
	{
		(*index)++;
		malloc_size++;
	}
	return (malloc_size);
}

int			find_texture(char *file_string, int *index, t_file_data *file_data,
						t_id_tuple *id_tuple)
{
	char	*path;
	char	*temp;
	int		malloc_size;
	int		i;

	i = 0;
	malloc_size = 0;
	loop_empty_space(file_string, index);
	temp = &(file_string[*index]);
	if (temp[0] != '.' && temp[1] != '/')
		return (0);
	malloc_size = texture_malloc_size(file_string, index);
	path = (char *)malloc(sizeof(char) * malloc_size + 1);
	if (!path)
		return (0);
	while (i < malloc_size)
	{
		path[i] = temp[i];
		i++;
	}
	path[i] = '\0';
	*(id_tuple->value) = path;
	loop_empty_space(file_string, index);
	return (1);
}
