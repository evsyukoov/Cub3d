/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 19:39:19 by denis             #+#    #+#             */
/*   Updated: 2020/07/10 18:13:45 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			init_dist_from_sprite(t_game *game)
{
	t_sprite_list *node;

	node = game->sprites;
	while (node)
	{
		node->distance = sqrt(powf(game->player->x * 1.0 / 64 - node->x, 2)
		+ powf(game->player->y * 1.0 / 64 - node->y, 2));
		node = node->next;
	}
}

int				get_texture_pixel(t_texture *texture,
t_spr_screen spr, int x, int y)
{
	int	color;
	int	text_x;
	int	text_y;

	text_x = (texture->width * 1.0 / spr.screen_size) * x;
	text_y = (texture->height * 1.0 / spr.screen_size) * y;
	color = get_texture_color(texture, text_x, text_y);
	return (color);
}

t_spr_screen	get_sprite_preferences(t_game *game, int sprite_index)
{
	t_sprite_list	*node;
	t_spr_screen	spr;
	float			theta;
	float			dx;
	float			dy;

	node = lstget(game->sprites, sprite_index);
	spr.dist = node->distance;
	dx = node->x - game->player->x * 1.0 / 64;
	dy = node->y - game->player->y * 1.0 / 64;
	theta = rad_to_deg(atan2(dy, dx));
	theta -= game->player->dir;
	if ((dx >= 0 && 180 <= game->player->dir && game->player->dir <= 360)
	|| (dx < 0 && dy < 0))
		theta += 360;
	spr.delta_rays = theta / (ONE_RAY_ANGLE(60, game->win_width));
	spr.screen_size = game->win_height / node->distance;
	spr.v_offset = (game->win_height - spr.screen_size) / 2;
	spr.h_offset = (game->win_width - spr.screen_size) / 2 + spr.delta_rays;
	return (spr);
}

void			draw_sprite_vert_line(t_game *game, t_spr_screen spr, int i)
{
	int j;
	int	color;

	j = 0;
	while (j < spr.screen_size)
	{
		if (j + spr.v_offset >= 0 && j + spr.v_offset < game->win_height)
		{
			color = get_texture_pixel(game->textures[SPRITE], spr, i, j);
			if (color)
				my_mlx_pixel_put(&game->image, i + spr.h_offset,
				j + spr.v_offset, game->f(color, spr.dist, 0.1));
		}
		j++;
	}
}
