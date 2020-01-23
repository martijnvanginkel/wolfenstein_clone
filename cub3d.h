/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:29:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/23 11:23:55 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "srcs/get_next_line/get_next_line.h"
// #include <stdlib.h>

int     find_strlen(char *str);
void    print_string(char *str);
// char    *strjoin(char *s1, char *s2);
char    *make_empty_string();
int     approve_map(int **map, int height);
void    show_error(char *error_message);


// # define BUFFER_SIZE 128


// int		get_next_line(int fd, char **line);
// void	set_and_free_values(char **waitingline, char **buf_result);
// int		continue_or_end(int *end_of_file, char **waitingline, char ***line);
// int		enough_for_one_line(char *line);
// char	*read_bufsize(int fd, int *end_of_file);
// char	*read_line(char **waitingline);
// char	*strjoin(char *s1, char *s2);
// int		get_strlen(char *str);

#endif