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

int 	check_begin_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void 		init_start_pos(t_game *game, char c, int i, int j)
{
	game->player->x = j * 64 + 32;
	game->player->y = i * 64 + 32;
	if (c == 'N')
		game->player->dir = 270;
	else if (c == 'W')
		game->player->dir = 0;
	else if (c == 'E')
		game->player->dir = 180;
	else
		game->player->dir = 90;
	//player->dir = degrees_to_rad(player->dir);
}

t_game		*init_game(int fd)
{
	void *mlx;
	t_game *game;
	t_list *lst;
	t_player *player;
	t_sprite_list *sprites;

	mlx = mlx_init();
	sprites = NULL;
	player = (t_player*)malloc(sizeof(t_player));
	game = (t_game*)malloc(sizeof(t_game));
	game->player = player;
	game->sprites = sprites;
	game->mlx = mlx;
	init_default_config(game);
	lst = reader(fd);
	parse_config(lst, game);
	check_map(game);
	init_sprite_list(game);
	game->sprites_list_size = lstsize(game->sprites);
	return (game);
}


