/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/06/04 15:37:35 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int 	render_next(t_game *game)
{
	raycaster(game, game->textures);
	return (1);
}

void 	print_config(t_game *game)
{
	char **map;
	map = game->map;
	int i = 0;
	printf("width = %d, height = %d\n", game->win_width, game->win_height);
	printf("ceiling color = %d, floor color = %d\n", game->ceiling_color, game->floor_color);
	while (map[i])
		printf("%s$\n", map[i++]);
}

void 	run(t_game *game)
{
	void *mlx_win;
	t_data image;

	mlx_win = mlx_new_window(game->mlx, game->win_width, game->win_height, "Cub3D");
	game->mlx_win = mlx_win;
	image.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel, &image.line_length, &image.endian);
	game->image = image;
	mlx_hook(game->mlx_win, 2, 1L << 0, &key_events, game);
	mlx_loop_hook(game->mlx, render_next, game);
	mlx_loop(game->mlx);
}

int     main(void) {
	t_game *game;
	int fd;

	fd = open("./Maps/cub1.cub", O_RDONLY);
	game = init_game(fd);
	printf("player x = %d, player y= %d\n", game->player->x, game->player->y);
	run(game);
}


