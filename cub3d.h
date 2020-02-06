/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:29:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/02/06 12:01:35 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "srcs/get_next_line/get_next_line.h"

typedef struct  s_data {
    void        *img;
	void		*mlx;
	void		*mlx_win;

    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct 	s_game_tile
{
	int			value;
	int			x;
	int			y;
	int			start_x;
	int			start_y;
}				t_game_tile;

typedef struct	s_game_manager
{
	t_game_tile		**map;
	int				map_height;
	int				map_width;
	int				tile_width;
	int				tile_height;

	t_game_tile		*player_tile;
	int				player_x;
	int				player_y;
	
	double			player_dir;
	double			x_dir;
	double			y_dir;

	t_data  		*img_data;
}				t_game_manager;

/* Struct that holds map_tile values */
typedef struct			s_map_tile
{
	int					value;
	int					x;
	int					y;	
	int					is_visited;
	struct s_map_tile 	*previous_tile;
}						t_map_tile;

/* Struct with all the file information */
typedef struct  s_file_data
{
    char        *full_file;
	
    t_map_tile  **map;
	int			map_width;
	int			map_height;

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
t_map_tile		**get_map(t_file_data *file_data, int index);
int				approve_map(t_map_tile **map, t_file_data *file_data);
int				get_general_info(t_file_data *file_data);
int				get_map_width(char *content_string, int index);
int             get_widest_map_line(char *content_string, int index);
int				get_map_height(char *content_string);
void			loop_till_next_line(char *str, int *index);
t_file_data		*get_file_data(int argc, char**argv);
t_file_data     *empty_file_data(void);
int            	all_info_filled(t_file_data *data);
void			print_file_data(t_file_data *file_data);
t_file_data		*collect_file_information(char *file_name);
int				find_resolution(char *file_string, int *index, t_file_data *data, t_id_tuple *id_tuple);
int				find_texture(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_tuple);
int				find_color(char *file_string, int *index, t_file_data *file_data, t_id_tuple *id_tuple);
void			free_map(t_file_data *file_data);

/* Window drawing */
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);

void			run_game(t_file_data *file_data);
t_data          setup_image_data(t_file_data *file_data);
t_game_manager	setup_game_manager(t_file_data *file_data, t_data *img);

void            draw_map(t_game_manager *game_manager);
void			draw_player(t_game_manager *game_manager);

void            update_player(t_game_manager *game_manager, int x_diff, int y_diff);


#endif