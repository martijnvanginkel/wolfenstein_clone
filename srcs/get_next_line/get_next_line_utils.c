/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 13:05:24 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/22 16:03:00 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*strjoin(char *s1, char *s2)
{
	char	*result;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (s1 == 0)
		return (0);
	result = malloc(sizeof(char) * (get_strlen(s1) + get_strlen(s2) + 1));
	if (!result)
		return (0);
	while (s1[x] != '\0')
	{
		result[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		result[x] = s2[y];
		x++;
		y++;
	}
	result[x] = '\0';
	return (result);
}

char		*cut_str_till(char *buf, int str_size)
{
	int		x;
	char	*result;

	x = 0;
	result = malloc(sizeof(char) * (str_size + 1));
	if (!result)
	{
		return (0);
	}
	while (x < str_size)
	{
		result[x] = buf[x];
		x++;
	}
	result[x] = '\0';
	return (result);
}

char		*make_new_line(char *old_line, int index)
{
	char	*new_wait_line;
	int		line_length;
	int		x;

	x = 0;
	line_length = get_strlen(old_line);
	new_wait_line = malloc(sizeof(char) * (line_length - index) + 1);
	if (!new_wait_line)
	{
		return (0);
	}
	while (old_line[index] != '\0')
	{
		new_wait_line[x] = old_line[index];
		index++;
		x++;
	}
	new_wait_line[x] = '\0';
	return (new_wait_line);
}

char		*read_line(char **waitingline)
{
	char	*result;
	char	*new_line;
	int		linelen;
	int		x;

	x = 0;
	result = 0;
	linelen = get_strlen(*waitingline);
	while (x < linelen)
	{
		if ((*waitingline)[x] == '\n')
		{
			result = cut_str_till(*waitingline, x + 1);
			new_line = make_new_line(*waitingline, x + 1);
			free(*waitingline);
			*waitingline = new_line;
			return (result);
		}
		x++;
	}
	return (0);
}

int			enough_for_one_line(char *line)
{
	int x;

	x = 0;
	if (line == 0)
	{
		return (0);
	}
	while (line[x] != '\0')
	{
		if (line[x] == '\n')
		{
			return (1);
		}
		x++;
	}
	return (0);
}
