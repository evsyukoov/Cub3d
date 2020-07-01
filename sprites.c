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

t_sprite_list	*lstlast(t_sprite_list *head)
{
	t_sprite_list *tmp;

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void		lstadd_back(t_sprite_list **head, t_sprite_list *node)
{
	t_sprite_list *last;

	if (!(*head))
	{
		//printf("!");
		(*head) = node;
		(*head)->next = NULL;
		return ;
	}
	last = lstlast((*head));
	last->next = node;
	node->next = NULL;
}

void 	init_dist_from_sprite(t_game *game)
{
	int i;
	t_sprite_list *node;

	i = 0;
	node = game->sprites;
	while (node)
	{
		node->distance = sqrt(powf(game->player->x * 1.0 / 64 - node->x, 2) + powf(game->player->y * 1.0 / 64 - node->y, 2));
		node = node->next;
	}
}

t_sprite_list 	*create_new_node(t_game *game, int x, int y)
{
	t_sprite_list *node;

	if (!(node = (t_sprite_list*)malloc(sizeof(t_sprite_list))))
		return (0);
	node->x = x + 0.5;
	node->y = y + 0.5;
	node->next = NULL;
	return (node);
}

void	init_sprite_list(t_game *game)
{
	int i;
	int j;
	char **map;
	t_sprite_list *node;

	i = 0;
	printf("adress = %p\n", game->sprites);
	map = game->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
			{
				node = create_new_node(game, j, i);
				lstadd_back(&(game->sprites), node);
			}
			j++;
		}
		i++;
	}
}

t_sprite_list	*lstget(t_sprite_list *head, int index)
{
	int i;

	i = 0;
	while (i < index && head)
	{
		i++;
		head = head->next;
	}
	if (index <= -1)
		return (0);
	return (head);
}

int 	get_texture_pixel(t_texture *texture, t_spr_screen spr, int x, int y)
{
	int color;

	int text_x = (texture->width * 1.0 /  spr.screen_size) * x;
	int text_y = (texture->height * 1.0 /  spr.screen_size) * y;
	color = get_texture_color(texture, text_x, text_y);
	return (color);

}

t_spr_screen	get_sprite_preferences(t_game *game, int sprite_index)
{
	t_sprite_list	*node;
	float			theta;
	float			dx;
	float 			dy;
	t_spr_screen	spr;

	node = lstget(game->sprites, sprite_index);
	spr.dist = node->distance;
	dx = node->x - game->player->x * 1.0 / 64;
	dy = node->y  - game->player->y * 1.0 / 64;
	theta = rad_to_deg(atan2(dy, dx));
	theta -= game->player->dir;
	if ((dx >= 0 && 180 <= game->player->dir && game->player->dir <= 360) || (dx < 0 && dy < 0))
		theta += 360;
	spr.delta_rays = theta / (one_ray_angle(60, game->win_width));
	spr.screen_size = game->win_height / node->distance;
	spr.v_offset = (game->win_height - spr.screen_size) / 2;
	spr.h_offset = (game->win_width - spr.screen_size) / 2 + spr.delta_rays;
	return (spr);
}

void 	draw_all_sprites(t_game *game, float *z_buff)
{
	int i;

	i = 0;
	init_dist_from_sprite(game);
	game->sprites = mergesort_list(game->sprites);
	t_sprite_list *spr = game->sprites;
	while (i < game->sprites_list_size) {
		draw_sprite(game, i, z_buff);
		i++;
	}
}

void 	draw_sprite(t_game *game, int sprite_index, float *z_buff)
{

	int color;
	int i;
	int j;
	t_spr_screen spr;

	i = 0;
	spr = get_sprite_preferences(game, sprite_index);
	while (i < spr.screen_size)
	{
		if (i + spr.h_offset >= 0 && i + spr.h_offset <= game->win_width
		&& z_buff[i + spr.h_offset] > spr.dist) {
			j = 0;
			while (j < spr.screen_size) {
				if (j + spr.v_offset >= 0 && j + spr.v_offset <= game->win_height) {
					color = get_texture_pixel(game->textures[SPRITE], spr, i, j);
					if (color)
						my_mlx_pixel_put(&game->image, i + spr.h_offset, j + spr.v_offset, color);
				}
				j++;
			}
		}
		i++;
	}
}