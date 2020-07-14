/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: denis <denis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 13:54:16 by denis             #+#    #+#             */
/*   Updated: 2020/07/11 13:35:51 by denis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int		check_top_border(int i, int j, char **map)
{
	while (i >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		i--;
	}
	return (0);
}

int		check_left_border(int i, int j, char **map)
{
	while (j >= 0)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		j--;
	}
	return (0);
}

int		check_bot_border(int i, int j, char **map, t_game *game)
{
	int height;

	height = game->map_height;
	while (i < height)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		i++;
	}
	return (0);
}

int		check_right_border(int i, int j, char **map, t_game *game)
{
	int width;

	width = game->map_width;
	while (j < width)
	{
		if (map[i][j] == '1')
			return (1);
		if (map[i][j] == ' ')
			return (0);
		j++;
	}
	return (0);
}

int		check_borders(int i, int j, char **map, t_game *game)
{
	if (check_bot_border(i, j, map, game) && check_left_border(i, j, map) &&
		check_right_border(i, j, map, game) && check_top_border(i, j, map))
		return (1);
	error("Wrong map!");
	return (0);
}
