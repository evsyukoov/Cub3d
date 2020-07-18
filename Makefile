# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: denis <denis@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/18 16:21:25 by denis             #+#    #+#              #
#    Updated: 2020/07/18 16:22:35 by denis            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

SRCS = Cub_src/bitmap.c \
		Cub_src/check_map_borders.c \
		Cub_src/color_utils.c \
		Cub_src/drawing_utils.c \
		Cub_src/init_game.c \
		Cub_src/main.c \
		Cub_src/map_utils.c \
		Cub_src/merge_sort.c \
		Cub_src/move_player.c \
		Cub_src/parser.c \
		Cub_src/parsing_utils.c \
		Cub_src/raycaster.c \
		Cub_src/raycaster_2.c \
		Cub_src/sprite_list_utils.c \
		Cub_src/sprites.c \
		Cub_src/utils.c \
		Cub_src/utils_2.c \
		GNL/get_next_line.c \
		GNL/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

FRAMEWORKS = -framework OpenGL -framework AppKit
LIB = -Llibft -lft -Lminilibx -lmlx

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft/
	make -C minilibx/
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIB) $(FRAMEWORKS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C libft/ clean
	make -C minilibx/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean
	make -C minilibx/ fclean

re: fclean all