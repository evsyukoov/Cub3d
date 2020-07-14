/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/09 17:11:43 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		my_exit(void)
{
	exit(0);
}

void	run(t_game *game)
{
	void	*mlx_win;
	t_data	image;

	mlx_win = mlx_new_window(game->mlx,
	game->win_width, game->win_height, "Cub3D");
	game->mlx_win = mlx_win;
	image.img = mlx_new_image(game->mlx,
	game->win_width, game->win_height);
	image.addr = mlx_get_data_addr(image.img,
	&image.bits_per_pixel, &image.line_length, &image.endian);
	game->image = image;
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image.img, 0, 0);
	mlx_hook(game->mlx_win, 2, 1L << 0, &action_listener, game);
	mlx_hook(game->mlx_win, 17, 0, &my_exit, game);
	mlx_loop(game->mlx);
}

void	screenshot(t_game *game)
{
	t_data image;

	image.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
	image.addr = mlx_get_data_addr(image.img,
	&image.bits_per_pixel, &image.line_length, &image.endian);
	game->image = image;
	raycaster(game);
	create_bmp(game);
}

int		main(int argc, char **argv)
{
	t_game	*game;
	int		fd;

	if (argc == 1 || argc > 3)
		error("Wrong number of arguments!");
	if (!str_endswith(argv[1], ".cub"))
		error("Wrong cub-config file extension!");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error("Cub-file dont't find\n");
	game = init_game(fd);
	if (argc == 2)
		run(game);
	else if (argc == 3 && ft_strncmp("--save", argv[2],
			ft_strlen(argv[2]) > 6 ? ft_strlen(argv[2]) : 6) == 0)
		screenshot(game);
	else
		error("Wrong arguments!\n");
	return (1);
}
