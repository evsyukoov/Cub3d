/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:05:42 by denis             #+#    #+#             */
/*   Updated: 2020/07/12 20:16:33 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		non_shadow(int color, float distance, float k)
{
	distance = 0;
	k = 0;
	return (color);
}

int		rgb_to_int(unsigned char r, unsigned char g, unsigned char b)
{
	return (r << 16) | (g << 8) | b;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	void	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(int*)dst = color;
}

int		get_color(t_data *data, int x, int y)
{
	void *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(int*)dst);
}

int		get_texture_color(t_texture *texture, int x, int y)
{
	void	*dst;

	dst = texture->addr + (y * texture->line_length + x
	* (texture->bits_per_pixel / 8));
	return (*(int*)dst);
}
