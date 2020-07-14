cmake_minimum_required(VERSION 3.16)
project(Cub C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -framework OpenGl -framework AppKit")
link_directories(/Users/denis/Denis/21School/Cub/GNL/
                /Users/denis/Denis/21School/Cub/minilibx/
                /Users/denis/Denis/21School/Cub/libft/)
add_executable(Cub /Users/denis/Denis/21School/Cub/Cub_src/main.c
        /Users/denis/Denis/21School/Cub/Cub_src/drawing_utils.c
        /Users/denis/Denis/21School/Cub/Cub_src/parser.c
        /Users/denis/Denis/21School/Cub/Cub_src/init_game.c
        /Users/denis/Denis/21School/Cub/Cub_src/utils.c
        /Users/denis/Denis/21School/Cub/Cub_src/move_player.c
        /Users/denis/Denis/21School/Cub/Cub_src/raycaster.c
        /Users/denis/Denis/21School/Cub/Cub_src/sprites.c
        /Users/denis/Denis/21School/Cub/Cub_src/merge_sort.c
        /Users/denis/Denis/21School/Cub/Cub_src/parsing_utils.c
        /Users/denis/Denis/21School/Cub/Cub_src/check_map_borders.c
        /Users/denis/Denis/21School/Cub/Cub_src/bitmap.c
        /Users/denis/Denis/21School/Cub/Cub_src/color_utils.c
        /Users/denis/Denis/21School/Cub/Cub_src/map_utils.c
        /Users/denis/Denis/21School/Cub/Cub_src/utils_2.c
        /Users/denis/Denis/21School/Cub/Cub_src/raycaster_2.c
        /Users/denis/Denis/21School/Cub/Cub_src/sprite_list_utils.c)
target_link_libraries(Cub gnl mlx ft)


