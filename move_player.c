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

/*int 	check_distanation(double x, double y)
{
	double x_fractional;
	double y_fractional;
	double compare;

	x_fractional = modf(x, &x_fractional);
	y_fractional = modf(y, &y_fractional);
	printf("fract y = %f, fract x = %f\n", y_fractional, x_fractional);

	if ((int)round(x) - x_fractional <= step && (int)round(y) - y_fractional <= step) {
		printf("eee\n");
		return (1);
	}
	return (0);
}*/

int 	check_wall(t_game *game, float side_dir)
{
	int x;
	int y;

	x = game->player->x;
	y = game->player->y;
	x += 64 * cos(degrees_to_rad(side_dir));
	y += 64 * sin (degrees_to_rad(side_dir));
	//printf("side_dir = %f\n", side_dir);
	//printf("new x = %d, new y = %d\n", x, y);
	if ((game->map)[y / 64][x / 64] == '1') {
		//printf("yo\n");
		return (0);
	}
	return (1);
}

void 	rotate(int key, t_player *player)
{
	if (key == 124) {
		player->dir = normalize_deg(player->dir + 10);
		printf("Rotate! curr_dir = %f\n", player->dir);
	}
	else {
		player->dir = normalize_deg(player->dir - 10);
		printf("Rotate! curr_dir = %f\n", player->dir);
	}
}

int		key_events(int key, t_game *game)
{
	double side_dir;
	double x;
	double y;
	float prev_x;
	float prev_y;
	t_ray ray;
	int flag;

	flag = 1;
	x = game->player->x;
	y = game->player->y;
	if (key == 53)
		exit(0);
	if (key == 123 || key == 124)
		rotate(key, game->player);
	if (key == 13 || key == 1 || key == 0 || key == 2) {
		if (key == 1) {
			side_dir = game->player->dir - 180;
			side_dir = normalize_deg(side_dir);
		}
		else if (key == 13) {
			//flag = check_forward(game);
			side_dir = game->player->dir;
		}
		else if (key == 0) {
			side_dir = game->player->dir - 90;
			side_dir = normalize_deg(side_dir);
		}
		if (key == 2) {
			side_dir = game->player->dir + 90;
			normalize_deg(side_dir);
		}
		prev_x = x;
		prev_y = y;
		if(check_wall(game, side_dir)) {
			game->player->x += step * cos(degrees_to_rad(side_dir));
			game->player->y += step * sin(degrees_to_rad(side_dir));
		}
			side_dir = normalize_deg(side_dir);

			//ray = raytracing(game, side_dir);
			//printf("player dir = %f, length to projection = %f\n",side_dir, ray.length);
			//printf("ray x = %f, ray y = %f\n",ray.x / 64, ray.y / 64);
			//printf("pos x = %d, pos y = %d\n", game->player->x / 64, game->player->y / 64);
			//printf("dir = %f\n", game->player->dir);
	}
	raycaster(game, game->textures);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image.img, 0, 0);
	//mlx_string_put(game->mlx, game->mlx_win, 50, 50, rgb_to_int(255,255,255), "HELLO WORLD!");
	return (0);
}
