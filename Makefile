# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-gin <mvan-gin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/22 09:47:24 by mvan-gin       #+#    #+#                 #
#    Updated: 2020/02/20 16:02:13 by mvan-gin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

FILES =		srcs/main.c \

U_FILES =	srcs/general/standards.c \
			srcs/general/dec_to_hex.c \
			srcs/general/rgb_to_hex.c \

MAP_FILES = srcs/file_reading/read_file.c \
			srcs/file_reading/read_file_utils.c \
			srcs/file_reading/find_map.c \
			srcs/file_reading/find_map_utils.c \
			srcs/file_reading/approve_map.c \
			srcs/file_reading/general_file_info.c \
			srcs/file_reading/find_resolution.c \
			srcs/file_reading/find_texture.c \
			srcs/file_reading/find_color.c \
			srcs/get_next_line/get_next_line.c \
			srcs/get_next_line/get_next_line_utils.c \

WIN_FILES =	srcs/win_drawing/update.c \
			srcs/win_drawing/quit_game.c \
			srcs/win_drawing/draw_map.c \
			srcs/win_drawing/setup_game.c \
			srcs/win_drawing/textures.c \
			srcs/win_drawing/update_player.c \
			srcs/win_drawing/drawing_utils.c \
			srcs/win_drawing/shoot_3d_rays.c \
			srcs/win_drawing/calculate_ray_utils.c \
			srcs/win_drawing/floor_and_ceiling.c \
			srcs/win_drawing/add_sprite_to_ray.c \
			

CC = gcc -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

$(NAME): fclean
	$(CC) $(FILES) $(MAP_FILES) $(WIN_FILES) $(U_FILES) -o game && ./game map.cub
# 	$(CC) $(FILES) $(MAP_FILES) -o $(NAME) && ./$(NAME)

# game: fclean

map_checker: fclean
	gcc $(MAP_FILES) -o map_checker && ./map_checker map.cub

clean:

fclean: clean
	rm -f $(NAME)
	rm -f map_checker

re: fclean all

