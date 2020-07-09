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

float 		get_vector_length(t_game *game, t_ray ray)
{
	return sqrt(pow(ray.x - game->player->x, 2) + pow(ray.y - game->player->y, 2));
}

float 		intersection_detector(t_game *game, t_ray *ray, float distance, float deg, int flag)
{
	//printf("map x = %d, map_y = %d\n", ray->map_x, ray->map_y);
	while (ray->map_x >= 0 && ray->map_y >= 0 && ray->map_x < game->map_width && ray->map_y < game->map_height) {
		if ((game->map)[ray->map_y][ray->map_x] == '1') {
			distance = get_vector_length(game, *ray);
			break;
		}
		ray->x += ray->delta_x;
		ray->y += ray->delta_y;
		ray->map_x = ((int) (ray->x / 64));
		ray->map_y = ((int) (ray->y / 64));
	}
	return (distance);
}

float 		vertical_tracing(t_game *game, double deg, t_ray *ray)
{
	float distance;
	int flag;

	flag = 0;
	if (is_looking_right(deg) == -1)
		flag = 1;
	distance = MAXFLOAT;
	ray->delta_x = (is_looking_right(deg) == 1 ? 64 : -64);
	if (deg == 90 || deg == 270)
		return (distance);
	ray->x = ((int)(game->player->x / 64) * 64) + (is_looking_right(deg) == 1 ? 64 : -0.0001);
	ray->y = game->player->y + (game->player->x - ray->x) * tan(degrees_to_rad(deg)) * (-1);
	ray->delta_y = ray->delta_x * tan(degrees_to_rad(deg));
	ray->map_x = ((int)(ray->x / 64));
	ray->map_y = ((int)(ray->y / 64));
	distance = intersection_detector(game, ray, distance, deg, flag);
	return (distance);
}


float 		horizontal_tracing(t_game *game, double deg, t_ray *ray)
{
	float distance;
	int flag = 0;

	distance = MAXFLOAT;
	if (is_looking_up(deg) == 1)
		flag = 1;
	ray->delta_y = 64 * (is_looking_up(deg) == 1 ? -1 : 1);
	if (deg == 0 || deg == 180 || deg == 360)
		return (distance);
	ray->y = ((int)(game->player->y / 64)) * 64 + (is_looking_up(deg) == 1 ? -0.0001 : 64);
	ray->x = game->player->x + (game->player->y - ray->y) / tan(degrees_to_rad(deg)) * (-1);
	ray->delta_x = ray->delta_y / tan(degrees_to_rad(deg));
	ray->map_x = ((int)(ray->x / 64));
	ray->map_y = ((int)(ray->y / 64));
	distance = intersection_detector(game, ray, distance, deg, flag);
	return (distance);
}

t_ray 	raytracing(t_game *game, float deg)
{
	t_ray ray1;
	t_ray ray2;
	t_ray ray;
	float dv;
	float dh;

	dv = vertical_tracing(game, deg, &ray1);
	dh = horizontal_tracing(game, deg, &ray2);
	if (dh <= dv) {
		ray.x = ray2.x;
		ray.y = ray2.y;
		if (is_looking_up(deg) == 1)
			ray.wall = NORTH;
		else
			ray.wall = SOUTH;
		ray.length = dh;
	}
	else {
		ray.x = ray1.x;
		ray.y = ray1.y;
		if (is_looking_right(deg) == 1)
			ray.wall = WEST;
		else
			ray.wall = EAST;
		ray.length = dv;
	}
	ray.perp_length = ray.length  * cos(degrees_to_rad(deg - game->player->dir));
	return (ray);
}

t_line 	find_vertical_line(t_game *game, t_ray ray, int x_pos, double deg)
{
	t_line line;
	double column_height;
	double s_pr;
	float d_proj;

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

void 	find_texture_x(t_game *game, t_ray *ray, t_texture **texture)
{
	if (ray->wall == SOUTH || ray->wall == NORTH)
	{
		ray->wall_x = ray->x / 64;
		ray->wall_x -= floor(ray->wall_x);
	} else
	{
		ray->wall_x = ray->y / 64;
		ray->wall_x -= floor(ray->wall_x);
	}
	texture[ray->wall]->text_x = (int)(ray->wall_x * texture[ray->wall]->width);
	if (ray->wall == EAST || ray->wall == SOUTH)
		texture[ray->wall]->text_x = texture[ray->wall]->width - texture[ray->wall]->text_x - 1;
}

int 	raycaster(t_game *game, t_texture **texture)
{
	float deg;
	t_ray ray;
	t_line vert_line;
	int x_vert_line_pos;
	float 	*z_buff;

	deg = normalize_deg(game->player->dir - 30);
	z_buff = (float*)malloc(sizeof(float) * game->win_width);
	x_vert_line_pos = 0;
	while (x_vert_line_pos <= game->win_width)
	{
		ray = raytracing(game, deg);
		z_buff[x_vert_line_pos] = ray.length / 64;
		find_texture_x(game, &ray, texture);
		vert_line = find_vertical_line(game, ray, x_vert_line_pos, deg);
		draw_line(game, ray, vert_line, texture);
		x_vert_line_pos++;
		deg += one_ray_angle(60, game->win_width);
		deg = normalize_deg(deg);
	}
	draw_all_sprites(game, z_buff, ray);
	free(z_buff);
	return (1);
}