/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:29:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/01/24 19:05:55 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include "srcs/get_next_line/get_next_line.h"

/* Struct with all the file information */
typedef struct  s_file_data
{
    char        *full_file;

    int         res_width;
    int         res_height;

    char        *north_texture;
    char        *south_texture;
    char        *west_texture;
    char        *east_texture;

    char        *sprite_texture;
    char        *floor_texture;
    char        *ceiling_texture;

    int         **map;
}               t_file_data;

/* Struct that holds the identifier_tag and the function that goes with it */
typedef struct  s_id_tuple
{
    char        *identifier;
    int        (*function)(char *, int *, t_file_data *);
}               t_id_tuple;

/* Standards */
int     find_strlen(char *str);
void    print_string(char *str);
char    *make_empty_string();
void    show_error(char *error_message);
int     same_string(char *s1, char *s2, int length);

/* File reading */
int     **allocate_map(char *content_string);
int     approve_map(int **map, int height);
int     get_general_info(t_file_data *file_data);
void    free_map(int **map);
int     get_map_width(char *content_string, int index);
int     get_map_height(char *content_string);
void    print_map(int **map, int height);






#endif