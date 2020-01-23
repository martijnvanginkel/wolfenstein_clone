# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mvan-gin <mvan-gin@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/01/22 09:47:24 by mvan-gin       #+#    #+#                 #
#    Updated: 2020/01/23 09:02:30 by mvan-gin      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

FILES = main.c \

MAP_FILES = srcs/map_checker.c \
			srcs/approve_map.c \
			srcs/standards.c \
			srcs/get_next_line/get_next_line.c \
			srcs/get_next_line/get_next_line_utils.c \

CC = gcc -Wall -Wextra -Werror -I minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

$(NAME):
	$(CC) $(FILES) -o $(NAME) && ./$(NAME)

map_checker: fclean
	gcc $(MAP_FILES) -o map_checker && ./map_checker map.cub

clean:

fclean: clean
	rm -f $(NAME)
	rm -f map_checker

re: fclean all

