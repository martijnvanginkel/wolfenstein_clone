/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:29:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/29 14:54:18 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include "srcs/get_next_line/get_next_line.h"

/* Struct that holds map_tile values */
typedef struct			s_map_tile
{
	int					value;
	int					x_cord;
	int					y_cord;
	int					is_visited;
	struct s_map_tile 	*previous_tile;
}						t_map_tile;

/* Struct with all the file information */
typedef struct  s_file_data
{
    char        *full_file;
    t_map_tile  **map;

    int         **resolution;

    char        **north_texture;
    char        **south_texture;
    char        **west_texture;
    char        **east_texture;

    char        **sprite_texture;
    int         **floor_color;
    int         **ceiling_color;

}               t_file_data;

/* Struct that holds the identifier_tag and the function that goes with it */
typedef struct  s_id_tuple
{
    char        *identifier;
    int        (*function)(char *, int *, t_file_data *, struct s_id_tuple *);
    void        **value;
}               t_id_tuple;

/* Standards */
int     find_strlen(char *str);
void    print_string(char *str);
char    *make_empty_string();
void    show_error(char *error_message);
int     same_string(char *s1, char *s2, int length);
int     is_empty_line(char *str, int index);
int     str_to_number(int *num_ptr, char *file_string, int *index);
void	loop_empty_space(char *file_string, int *index);

/* File reading */
t_map_tile	**get_map(char *content_string);
// int			**allocate_map(char *content_string);
int			approve_map(t_map_tile **map);
int			get_general_info(t_file_data *file_data);
// void		free_map(int **map);
int			get_map_width(char *content_string, int index);
int			get_map_height(char *content_string);
// void		print_map(int **map, int height);

t_file_data     empty_file_data(void);
int            	all_info_filled(t_file_data *data);
void			print_file_data(t_file_data *file_data);


int		find_resolution(char *file_string, int *index, t_file_data *data, t_id_tuple *id_tuple);
int		find_texture(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_tuple);
int		find_color(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_tuple);






#endif