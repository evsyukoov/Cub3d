/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 17:29:08 by denis             #+#    #+#             */
/*   Updated: 2020/07/10 17:37:46 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

float	get_vector_length(t_game *game, t_ray ray)
{
	float delta_x;
	float delta_y;

	delta_x = ray.x - game->player->x;
	delta_y = ray.y - game->player->y;
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

float	intersection_detector(t_game *game, t_ray *ray, float distance)
{
	while (ray->map_x >= 0 && ray->map_y >= 0 &&
	ray->map_x < game->map_width && ray->map_y < game->map_height)
	{
		if ((game->map)[ray->map_y][ray->map_x] == '1')
		{
			distance = get_vector_length(game, *ray);
			break ;
		}
		ray->x += ray->delta_x;
		ray->y += ray->delta_y;
		ray->map_x = ((int)(ray->x / 64));
		ray->map_y = ((int)(ray->y / 64));
	}
	return (distance);
}

float	vertical_tracing(t_game *game, double deg, t_ray *ray)
{
	float	distance;

	distance = MAXFLOAT;
	ray->delta_x = (is_looking_right(deg) == 1 ? 64 : -64);
	if (deg == 90 || deg == 270)
		return (distance);
	ray->x = (int)((game->player->x / 64) * 64) +
	(is_looking_right(deg) == 1 ? 64 : -0.001);
	ray->y = game->player->y + (game->player->x - ray->x)
	* tan(degrees_to_rad(deg)) * (-1);
	ray->delta_y = ray->delta_x * tan(degrees_to_rad(deg));
	ray->map_x = ((int)(ray->x / 64));
	ray->map_y = ((int)(ray->y / 64));
	distance = intersection_detector(game, ray, distance);
	return (distance);
}

float	horizontal_tracing(t_game *game, double deg, t_ray *ray)
{
	float distance;

	distance = MAXFLOAT;
	ray->delta_y = 64 * (is_looking_up(deg) == 1 ? -1 : 1);
	if (deg == 0 || deg == 180 || deg == 360)
		return (distance);
	ray->y = (int)((game->player->y / 64) * 64) +
	(is_looking_up(deg) == 1 ? -0.001 : 64);
	ray->x = game->player->x + (game->player->y - ray->y)
	/ tan(degrees_to_rad(deg)) * (-1);
	ray->delta_x = ray->delta_y / tan(degrees_to_rad(deg));
	ray->map_x = ((int)(ray->x / 64));
	ray->map_y = ((int)(ray->y / 64));
	distance = intersection_detector(game, ray, distance);
	return (distance);
}

t_ray	analize_ray(t_game *game, float deg)
{
	t_ray ray1;
	t_ray ray2;
	t_ray ray;
	float dv;
	float dh;

	dv = vertical_tracing(game, deg, &ray1);
	dh = horizontal_tracing(game, deg, &ray2);
	if (dh < dv)
		north_or_south_wall(&ray, ray2, dh, deg);
	else
		west_or_east_wall(&ray, ray1, dv, deg);
	ray.perp_length = ray.length
	* cos(degrees_to_rad(deg - game->player->dir));
	return (ray);
}
