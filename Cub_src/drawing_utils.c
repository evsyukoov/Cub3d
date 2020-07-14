/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/10 18:13:23 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		shadow_wall(int color, float distance, float k)
{
	unsigned char rgb[4];

	int_to_bytes(color, rgb);
	rgb[2] = (int)(rgb[2] / (1 + distance * distance * k));
	rgb[1] = (int)(rgb[1] / (1 + distance * distance * k));
	rgb[0] = (int)(rgb[0] / (1 + distance * distance * k));
	return (rgb_to_int(rgb[2], rgb[1], rgb[0]));
}

void	draw_texture(t_game *game, t_ray ray, t_line line)
{
	int		color;
	float	text_y_step;
	float	text_pos;
	int		i;

	i = line.top;
	text_y_step = 1.0 * game->textures[ray.wall]->height / line.column_height;
	text_pos = (i - game->win_height / 2 + line.column_height / 2)
	* text_y_step;
	while (i < line.bot)
	{
		game->textures[ray.wall]->text_y = (int)text_pos
		& (game->textures[ray.wall]->height - 1);
		text_pos += text_y_step;
		color = get_texture_color(game->textures[ray.wall],
		game->textures[ray.wall]->text_x, game->textures[ray.wall]->text_y);
		my_mlx_pixel_put(&game->image, line.x_pos, i,
		game->f(color, ray.perp_length, 0.0001));
		i++;
	}
}

void	draw_line(t_game *game, t_ray ray, t_line line)
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

void	draw_all_sprites(t_game *game, float *z_buff)
{
	int				i;

	i = 0;
	init_dist_from_sprite(game);
	game->sprites = mergesort_list(game->sprites);
	while (i < game->sprites_list_size)
	{
		draw_sprite(game, i, z_buff);
		i++;
	}
}

void	draw_sprite(t_game *game, int sprite_index, float *z_buff)
{
	int				i;
	t_spr_screen	spr;

	i = 0;
	spr = get_sprite_preferences(game, sprite_index);
	while (i < spr.screen_size)
	{
		if (i + spr.h_offset >= 0 && i + spr.h_offset < game->win_width
				&& z_buff[i + spr.h_offset] > spr.dist)
			draw_sprite_vert_line(game, spr, i);
		i++;
	}
}
