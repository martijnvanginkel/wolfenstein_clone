# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-gin <mvan-gin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/22 09:47:24 by mvan-gin       #+#    #+#                 #
#    Updated: 2020/01/31 11:51:54 by mvan-gin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

FILES = srcs/main.c \

MAP_FILES = srcs/file_reading/read_file.c \
			srcs/file_reading/read_file_utils.c \
			srcs/file_reading/find_map.c \
			srcs/file_reading/find_map_utils.c \
			srcs/file_reading/approve_map.c \
			srcs/file_reading/general_file_info.c \
			srcs/file_reading/find_resolution.c \
			srcs/file_reading/find_texture.c \
			srcs/file_reading/find_color.c \
			srcs/standards.c \
			srcs/get_next_line/get_next_line.c \
			srcs/get_next_line/get_next_line_utils.c \

DRAW_FILES =	srcs/win_drawing/update.c \
				srcs/win_drawing/draw_map.c \

CC = gcc -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

$(NAME): fclean
	$(CC) $(FILES) $(MAP_FILES) -o $(NAME) && ./$(NAME)

game: fclean
	$(CC) $(FILES) $(MAP_FILES) $(DRAW_FILES) -o game && ./game

map_checker: fclean
	gcc $(MAP_FILES) -o map_checker && ./map_checker map.cub

clean:

fclean: clean
	rm -f $(NAME)
	rm -f map_checker

re: fclean all

