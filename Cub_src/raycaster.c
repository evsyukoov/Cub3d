/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:25:40 by denis             #+#    #+#             */
/*   Updated: 2020/07/10 17:34:03 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	north_or_south_wall(t_ray *result, t_ray ray, float dist, float deg)
{
	result->x = ray.x;
	result->y = ray.y;
	if (is_looking_up(deg) == 1)
		result->wall = NORTH;
	else
		result->wall = SOUTH;
	result->length = dist;
}

void	west_or_east_wall(t_ray *result, t_ray ray, float dist, float deg)
{
	result->x = ray.x;
	result->y = ray.y;
	if (is_looking_right(deg) == 1)
		result->wall = EAST;
	else
		result->wall = WEST;
	result->length = dist;
}

t_line	find_vertical_line(t_game *game, t_ray ray, int x_pos)
{
	t_line line;
	double column_height;

	column_height = game->win_height * 64 / ray.perp_length;
	line.column_height = column_height;
	line.top = game->win_height / 2 - column_height / 2;
	if (line.top < 0)
		line.top = 0;
	line.bot = game->win_height / 2 + column_height / 2;
	if (line.bot > game->win_height)
		line.bot = game->win_height;
	line.x_pos = x_pos;
	return (line);
}

void	find_texture_x(t_game *game, t_ray *ray)
{
	if (ray->wall == SOUTH || ray->wall == NORTH)
	{
		ray->wall_x = ray->x / 64;
		ray->wall_x -= floor(ray->wall_x);
	}
	else
	{
		ray->wall_x = ray->y / 64;
		ray->wall_x -= floor(ray->wall_x);
	}
	game->textures[ray->wall]->text_x = (int)
	(ray->wall_x * game->textures[ray->wall]->width);
	if (ray->wall == EAST || ray->wall == SOUTH)
		game->textures[ray->wall]->text_x = game->textures[ray->wall]->width
		- game->textures[ray->wall]->text_x - 1;
}

int		raycaster(t_game *game)
{
	float	deg;
	t_ray	ray;
	t_line	vert_line;
	int		x_vert_line_pos;
	float	*z_buff;

	deg = normalize_deg(game->player->dir - 30);
	if (!(z_buff = (float*)malloc(sizeof(float) * (game->win_width + 1))))
		error("Malloc error!");
	x_vert_line_pos = 0;
	while (x_vert_line_pos < game->win_width)
	{
		ray = analize_ray(game, deg);
		z_buff[x_vert_line_pos] = ray.length / 64;
		find_texture_x(game, &ray);
		vert_line = find_vertical_line(game, ray, x_vert_line_pos);
		draw_line(game, ray, vert_line);
		x_vert_line_pos++;
		deg += ONE_RAY_ANGLE(60, game->win_width);
		deg = normalize_deg(deg);
	}
	draw_all_sprites(game, z_buff);
	free(z_buff);
	return (1);
}
