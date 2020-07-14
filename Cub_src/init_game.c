/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/09 18:24:02 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int			init_default_config(t_game *game)
{
	int			i;
	t_texture	**textures;
	t_texture	*texture;

	i = 0;
	if (!(textures = (t_texture**)malloc(sizeof(t_texture*) * 5)))
		return (0);
	game->textures = textures;
	while (i < 5)
	{
		texture = (t_texture*)malloc(sizeof(t_texture));
		(game->textures)[i] = texture;
		game->textures[i]->img = NULL;
		i++;
	}
	game->win_width = DEFAULT;
	game->win_height = DEFAULT;
	game->floor_color = DEFAULT;
	game->ceiling_color = DEFAULT;
	return (1);
}

int			is_full_config(t_game *game)
{
	int i;

	i = 0;
	if (game->win_height == DEFAULT || game->win_width == DEFAULT
	|| game->floor_color == DEFAULT || game->ceiling_color == DEFAULT)
		return (0);
	while (i < 5)
	{
		if (game->textures[i]->img == NULL)
			return (0);
		i++;
	}
	return (1);
}

int			check_begin_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

void		init_start_pos(t_game *game, char c, int i, int j)
{
	game->player->x = j * 64 + 32;
	game->player->y = i * 64 + 32;
	if (c == 'N')
		game->player->dir = 270;
	else if (c == 'W')
		game->player->dir = 180;
	else if (c == 'E')
		game->player->dir = 0;
	else
		game->player->dir = 90;
}

t_game		*init_game(int fd)
{
	void			*mlx;
	t_game			*game;
	t_list			*lst;
	t_player		*player;
	t_sprite_list	*sprites;

	mlx = mlx_init();
	sprites = NULL;
	if (!(player = (t_player*)malloc(sizeof(t_player))))
		error("Malloc error!");
	if (!(game = (t_game*)malloc(sizeof(t_game))))
		error("Malloc error!");
	game->player = player;
	game->sprites = sprites;
	game->f = non_shadow;
	game->mlx = mlx;
	init_default_config(game);
	lst = reader(fd);
	parse_config(lst, game);
	check_map(game);
	init_sprite_list(game);
	game->sprites_list_size = lstsize(game->sprites);
	return (game);
}
