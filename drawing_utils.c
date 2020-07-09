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

int    rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16) | (g << 8) | b;
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(long*)dst = color;
}

int 		get_color(t_data *data, int x, int y)
{
	void *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int*)dst);
}

int 		get_texture_color(t_texture *texture, int x, int y)
{
	void 	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(int*)dst);
}

int 	shadow_wall(int color, float distance, float k)
{
	unsigned char rgb[4];

	int_to_bytes(color, rgb);
	rgb[2] = (int)(rgb[2] / (1 + distance * distance * k));
	rgb[1] = (int)(rgb[1] / (1 + distance * distance * k));
	rgb[0] = (int)(rgb[0] / (1 + distance * distance * k));
	return rgb_to_int(rgb[2], rgb[1], rgb[0]);
}

void 	draw_texture(t_game *game, t_ray ray, t_line line)
{
	int color;
	float text_y_step;
	float text_pos;
	int i;


	i = line.top;
	text_y_step = 1.0 * game->textures[ray.wall]->height / line.column_height;
	text_pos = (i - game->win_height / 2 + line.column_height / 2) * text_y_step;
	while (i < line.bot)
	{
		game->textures[ray.wall]->text_y = (int)text_pos & (game->textures[ray.wall]->height - 1);
		text_pos += text_y_step;
		color = get_texture_color(game->textures[ray.wall], game->textures[ray.wall]->text_x,
									  game->textures[ray.wall]->text_y);

		my_mlx_pixel_put(&game->image, line.x_pos, i, shadow_wall(color, ray.perp_length, 0.0001));
		i++;
	}
}

void 	draw_line(t_game *game, t_ray ray, t_line line, t_texture **texture)
{
	int i;

	i = 0;
	while (i < line.top)
	{
		my_mlx_pixel_put(&game->image, line.x_pos, i, game->ceiling_color);
		i++;
	}
	draw_texture(game, ray, line);
	i = line.bot;
	while (i < game->win_height)
	{
		my_mlx_pixel_put(&game->image, line.x_pos, i, game->floor_color);
		i++;
	}
}




