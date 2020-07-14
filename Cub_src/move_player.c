/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/12 20:18:16 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_wall(t_game *game, float side_dir)
{
	int x;
	int y;

	x = game->player->x;
	y = game->player->y;
	x += 64 * cos(degrees_to_rad(side_dir));
	y += 64 * sin(degrees_to_rad(side_dir));
	if ((game->map)[y / 64][x / 64] == '1')
		return (0);
	return (1);
}

void	rotate(int key, t_player *player)
{
	if (key == 124)
		player->dir = normalize_deg(player->dir + 10);
	if (key == 123)
		player->dir = normalize_deg(player->dir - 10);
}

void	ligtning_info(int key, t_game *game)
{
	if (key == 18)
		game->f = non_shadow;
	if (key == 19)
		game->f = shadow_wall;
}

int		action_listener(int key, t_game *game)
{
	double side_dir;

	ligtning_info(key, game);
	if (key == 53)
		exit(0);
	rotate(key, game->player);
	if (key == 13 || key == 1 || key == 0 || key == 2)
	{
		if (key == 1)
			side_dir = normalize_deg(game->player->dir - 180);
		else if (key == 13)
			side_dir = game->player->dir;
		else if (key == 0)
			side_dir = normalize_deg(game->player->dir - 90);
		if (key == 2)
			side_dir = normalize_deg(game->player->dir + 90);
		if (check_wall(game, side_dir))
		{
			game->player->x += STEP * cos(degrees_to_rad(side_dir));
			game->player->y += STEP * sin(degrees_to_rad(side_dir));
		}
	}
	raycaster(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image.img, 0, 0);
	return (0);
}
