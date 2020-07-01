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
	return (r << 16) + (g << 8) + b;
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(long*)dst = color;
}

int 		get_texture_color(t_texture *texture, int x, int y)
{
	void 	*dst;

	dst = texture->addr + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(int*)dst);
}

void 	draw_line(t_game *game, t_ray ray, t_line line, t_texture **texture)
{
	int i;
	int color;
	float text_y_step;
	float text_pos;

	//printf("bot = %d, top = %d\n", (int) line.bot, (int) line. top)
	i = 0;
	while (i < (int) line.top)
	{
		my_mlx_pixel_put(&game->image, line.x_pos, i, game->ceiling_color);
		i++;
	}
	text_y_step = 1.0 * texture[ray.wall]->height / line.column_height;
	text_pos = (i - game->win_height / 2 + line.column_height / 2) * text_y_step;
	while (i < (int) line.bot)
	{
		texture[ray.wall]->text_y = (int)text_pos & (texture[ray.wall]->height - 1);
		text_pos += text_y_step;
		color = get_texture_color(texture[ray.wall], texture[ray.wall]->text_x, texture[ray.wall]->text_y);
		my_mlx_pixel_put(&game->image, line.x_pos, i, color);
		i++;
	}
	while (i < game->win_height)
	{
		my_mlx_pixel_put(&game->image, line.x_pos, i, game->floor_color);
		i++;
	}
}

void            put_rectangle(t_data *img, t_image *format, int color)
{
	int i;
	int j;

	i = format->y_start;
	while (i < format->height + format->y_start)
	{
		j = format->x_start;
		while (j < format->width + format->x_start)
		{
			my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}



