/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/19 13:07:10 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/22 12:00:47 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 128

# include <stdlib.h>
# include <unistd.h>

int		get_next_line(int fd, char **line);
void	set_and_free_values(char **waitingline, char **buf_result);
int		continue_or_end(int *end_of_file, char **waitingline, char ***line);
int		enough_for_one_line(char *line);
char	*read_bufsize(int fd, int *end_of_file);
char	*read_line(char **waitingline);
char	*strjoin(char *s1, char *s2);
int		get_strlen(char *str);

#endif
