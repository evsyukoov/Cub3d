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

/*int 	render_next(t_game *game)
{
	//mlx_destroy_image(game->mlx, game->image.img);
	draw_player_pos(&game->image, game->player, 255 << 8);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->image.img, 0, 0);
}*/

void 	draw_player_pos(t_data *img, t_player *player, int color)
{
	int i;
	int j;
	int width;

	i = player->y - 10;
	while (i < 10 + player->y)
	{
		j = player->x - 10;
		while (j < 10 + player->x)
		{
			if (i == player->x && j == player->y)
				my_mlx_pixel_put(img, j, i, 255 << 16);
			else
				my_mlx_pixel_put(img, j, i, color);
			j++;
		}
		i++;
	}
}


