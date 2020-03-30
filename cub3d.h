/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-gin <mvan-gin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/22 14:29:17 by mvan-gin       #+#    #+#                */
/*   Updated: 2020/03/12 16:36:48 by mvan-gin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "srcs/get_next_line/get_next_line.h"

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

typedef struct  s_data {
    void        *img;
	void		*mlx;
	void		*mlx_win;

    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
	int			width;
	int			height;
}               t_data;

typedef struct 	s_game_tile
{
	int			value;
	int			x;
	int			y;
	int			start_x;
	int			start_y;
}				t_game_tile;

typedef struct	s_sprite_hit_data
{
	float		angle;
	float		angle_x_dir;
	float		angle_y_dir;
	float		ray_hit_point;
	float		perp_hit_point;
	float		perp_point_incr;
	float		ray_point_incr;
	float		tile_middle_x;
	float		tile_middle_y;
}				t_sprite_hit_data;

/* temp ? */
typedef struct	s_sprite
{
	float			eucl_dist;
	float			percentage;

	float			tile_middle_x;
	float			tile_middle_y;
	float			angle;
	float			angle_x_dir;
	float			angle_y_dir;
	float			ray_hit_point;
	float			perp_hit_point;
	float			perp_point_incr;
	float			ray_point_incr;

	struct s_sprite	*next_sprite;
}				t_sprite;

typedef struct  s_ray_info
{
	float		ray_dir;
	float		ray_x_dir;
	float		ray_y_dir;

    float       side_dist_x;
    float       side_dist_y;
    float       delta_dist_x;
    float       delta_dist_y;
	float		final_dist;

	float		perp_dist;
	float		eucl_dist;
	int			side_hit; /* 0 = NO | 1 = EA | 2 = SO | 3 == WE */


	int			has_sprite;
	t_sprite	sprite;


	t_game_tile	*tile_hit;
}               t_ray_info;

typedef struct	s_texture_images
{
	t_data		*north_tex;
	t_data		*east_tex;
	t_data		*west_tex;
	t_data		*south_tex;
	t_data		*sprite_tex;
}				t_texture_images;

typedef struct	s_game_manager
{
	t_game_tile		**map;

	t_file_data		*file_data;
	int				tile_width;
	int				tile_height;

	t_game_tile		*player_tile;
	float			player_x;
	float			player_y;
	
	float			player_dir; /* m_pi / radiant value that the player is looking at*/
	float			x_dir;		/* Relative x-position that the player is looking at */
	float			y_dir;

	t_texture_images	*textures;

	t_data  		*map_image;
	t_data			*world_image;
}				t_game_manager;

typedef struct  s_coordinates
{
    float         x;
    float         y;
}               t_coordinates;

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
char	make_upper_on_yes(char c, int yes);
char	*dec_to_hex(long dec_num, int is_upper);
int		ft_atoi(char *str);
int     dec_from_hex_color(int *rgb_code);

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

/* Drawing utils */
void            my_mlx_pixel_put(t_game_manager *gm, int x, int y, int color);
void            my_mlx_pixel_put2(t_game_manager *gm, int x, int y, int color);
void            my_image_put(t_data *img_data, t_coordinates cords, t_data *img_data2, t_coordinates cords2, t_game_manager *gm);
void			draw_2d_vision_line(t_game_manager *game_manager, double dir, int color);
// void			clean_3d_wall_line(t_game_manager *game_manager, int x_value);
// void			draw_3d_wall_line(t_game_manager *game_manager, int res_i, t_ray_info ray);
void			draw_floor_and_ceiling(t_game_manager *game_manager);

/* Update */
void			run_game(t_file_data *file_data);
t_data          setup_image_data(t_file_data *file_data);
t_game_manager	setup_game_manager(t_file_data *file_data, t_data *img, t_data *img2);
void			quit_game(t_game_manager *gm);

/* Textures */
void			get_textures(t_game_manager *gm);

/* Draw map */
void            draw_map(t_game_manager *game_manager); // temp
void			draw_grid(t_game_manager *game_manager); // temp

/* Update player */
void            rotate_player(t_game_manager *game_manager, double rotation);
void			move_player(t_game_manager *game_manager, double walk_speed);
int				available_pixel(t_game_manager *g_m, int x, int y);

/* Calculate ray utils */
void			calculate_side_distances(t_game_manager *game_manager, t_ray_info *ray_info);
void			calculate_deltas(t_game_manager *game_manager, t_ray_info *ray_info);
void			calculate_steps(t_ray_info *ray_info, int *step_x, int *step_y);

/* Shoot 3d rays */
void			shoot_rays(t_game_manager *game_manager, float player_dir, int color);

#endif