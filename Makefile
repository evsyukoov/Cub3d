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
LIB = libft/libft.a minilibx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(LIB) $(FRAMEWORKS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all