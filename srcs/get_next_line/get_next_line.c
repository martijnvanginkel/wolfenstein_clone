/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 16:25:38 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/22 15:24:57 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_strlen(char *str)
{
	int x;

	x = 0;
	if (!str)
	{
		return (0);
	}
	while (str[x] != '\0')
	{
		x++;
	}
	return (x);
}

char		*read_bufsize(int fd, int *end_of_file)
{
	char			*result;
	char			buf[BUFFER_SIZE + 1];
	int				bytes_read;
	int				x;

	x = 0;
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == -1)
		return (0);
	if (bytes_read == 0)
		*end_of_file = 1;
	buf[BUFFER_SIZE] = '\0';
	result = malloc(sizeof(char) * (bytes_read + 1));
	if (!result)
		return (0);
	while (x < bytes_read)
	{
		result[x] = buf[x];
		x++;
	}
	result[x] = '\0';
	return (result);
}

int			continue_or_end(int *end_of_file, char **waitingline, char ***line)
{
	if (*end_of_file == 1)
	{
		**line = *waitingline;
		*waitingline = 0;
		free(*waitingline);
		return (0);
	}
	**line = read_line(waitingline);
	return (1);
}

void		set_and_free_values(char **waitingline, char **buf_result)
{
	char	*temp;

	temp = *waitingline;
	*waitingline = strjoin(*waitingline, *buf_result);
	free(temp);
	free(*buf_result);
	return ;
}

int			get_next_line(int fd, char **line)
{
	static char		*waitingline;
	int				end_of_file;
	char			*buf_result;

	if (!line)
		return (-1);
	end_of_file = 0;
	while (!enough_for_one_line(waitingline) && end_of_file != 1)
	{
		if (waitingline == 0)
		{
			waitingline = read_bufsize(fd, &end_of_file);
			if (!waitingline)
				return (-1);
		}
		else
		{
			buf_result = read_bufsize(fd, &end_of_file);
			if (!buf_result)
				return (-1);
			set_and_free_values(&waitingline, &buf_result);
		}
	}
	return (continue_or_end(&end_of_file, &waitingline, &line));
}
