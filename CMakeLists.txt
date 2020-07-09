cmake_minimum_required(VERSION 3.16)
project(Cub C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGl -framework AppKit")
link_directories(/Users/denis/Denis/21School/Cub/GNL/
                /Users/denis/Denis/21School/Cub/minilibx/
                /Users/denis/Denis/21School/Cub/libft/)
add_executable(Cub main.c drawing_utils.c parser.c init_player.c utils.c move_player.c raycaster.c
        2DHelpers.c

        sprites.c
        merge_sort.c
        parsing_utils.c
        check_map_borders.c
       bitmap.c
        )
target_link_libraries(Cub gnl mlx ft)


